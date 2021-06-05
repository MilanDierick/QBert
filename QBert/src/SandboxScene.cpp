﻿#include "hlpch.h"
#include "SandboxScene.h"

#include "SandboxLevelSettings.h"
#include "Components/DiskMovementController.h"
#include "Components/HealthComponent.h"
#include "Components/QBertMovementController.h"
#include "Components/ScoreComponent.h"
#include "Components/TileComponent.h"
#include "HexagonalGrid/HexagonalGrid.h"

#define PYRAMID_WIDTH 7

using Json = nlohmann::json;
using namespace Heirloom;

SandboxScene::SandboxScene(const std::string& sceneName)
	: Scene(sceneName),
	  m_CameraController(1280.0f / 960.0f),
	  m_HexagonalGridLayout({ORIENTATION_POINTY, {1.0f, 0.85f}, {0.0f, 0.0f}}) { ReadConfigFile(); }

void SandboxScene::OnLoad()
{
	HL_PROFILE_FUNCTION()

	HL_INFO("Loading SandboxScene...");

	CreatePyramid(Configuration.PyramidWidth);

	const auto qbert1Texture = Texture2D::Create(Configuration.QBertTexture);

	const auto qbertSprite = Heirloom::CreateRef<Sprite>(Sprite(glm::vec3(0.0f, 0.0f, -1.0f),
																glm::vec2(1.0f),
																0.0f,
																qbert1Texture,
																1.0f,
																glm::vec4(1.0f)));
	auto qbertGameObject      = Heirloom::CreateRef<GameObject>(this);
	auto qbertSpriteRenderer  = qbertGameObject->AddComponent(Heirloom::CreateRef<SpriteRenderer>());
	auto qbertHealthComponent = qbertGameObject->AddComponent(
		Heirloom::CreateRef<HealthComponent>(Configuration.MaximumHealth, Configuration.StartHealth));

	qbertSpriteRenderer->SetSprite(qbertSprite);
	const auto movementController = qbertGameObject->AddComponent(Heirloom::CreateRef<QBertMovementController>(
		Configuration.TicksBetweenMoves,
		Configuration.TicksPerMove,
		Hex(static_cast<int>(Configuration.InitialQBertPosition.x),
			static_cast<int>(Configuration.InitialQBertPosition.y),
			-static_cast<int>(Configuration.InitialQBertPosition.z)),
		qbertGameObject));

	qbertSpriteRenderer->SetSpriteOffset(glm::vec3{0.0f, m_HexagonalGridLayout.Size.y * 1.25f, -1.0f});

	qbertHealthComponent->RegisterOutOfBoundsEventHandler(movementController);

	const Ref<Texture2D> diskTexture = Texture2D::Create(Configuration.DiskTexture);

	const Ref<Sprite> diskSprite = CreateRef<Sprite>(Sprite(glm::vec3(0.0f, 0.0f, -1.0f),
															glm::vec2(1.0f),
															0.0f,
															diskTexture,
															1.0f,
															glm::vec4(1.0f)));

	Ref<GameObject> disk1GameObject         = CreateRef<GameObject>(this);
	Ref<SpriteRenderer> disk1SpriteRenderer = disk1GameObject->AddComponent(CreateRef<SpriteRenderer>());

	disk1SpriteRenderer->SetSprite(diskSprite);

	disk1GameObject->AddComponent(CreateRef<DiskMovementController>(Hex(5, 2, -7),
																	m_HexagonalGridLayout,
																	0,
																	0,
																	250,
																	CreateRef<std::unordered_set<Hex>>(m_Grid),
																	disk1GameObject));

	m_GameObjects.push_back(disk1GameObject);

	Ref<GameObject> scoreObject = CreateRef<GameObject>(this);
	scoreObject->AddComponent(CreateRef<ScoreComponent>(scoreObject, 0));

	m_GameObjects.push_back(scoreObject);

	// This mess is to center the pyramid in the viewport, can this be made easier?
	const Hex hex = *m_Grid.find(Hex(static_cast<int>(Configuration.CameraHexPosition.x),
									 static_cast<int>(Configuration.CameraHexPosition.y),
									 static_cast<int>(Configuration.CameraHexPosition.z)));
	glm::vec3 finalCameraPosition = glm::vec3(HexagonalGrid::HexToPixel(m_HexagonalGridLayout, hex), 0.0f);
	m_CameraController.SetCameraPosition(finalCameraPosition);
	m_CameraController.SetZoomLevel(Configuration.InitialZoomLevel);

	m_GameObjects.push_back(qbertGameObject);
}

void SandboxScene::OnUnload()
{
	HL_PROFILE_FUNCTION()

	HL_INFO("Unloading SandboxScene...");
}

void SandboxScene::OnUpdate()
{
	HL_PROFILE_FUNCTION()

	for (const Ref<GameObject> gameObject : m_GameObjects) { gameObject->Update(Timestep{0.016f}); }

	const auto newEndIterator = std::ranges::remove_if(m_GameObjects,
													   [](Ref<GameObject> gameObject)
													   {
														   if (!gameObject->IsActive())
														   {
															   gameObject.reset();
															   return true;
														   }
														   return false;
													   }).begin();

	m_GameObjects.erase(newEndIterator, std::end(m_GameObjects));
}

void SandboxScene::OnRender()
{
	HL_PROFILE_FUNCTION()

	RenderCommand::SetClearColor(Configuration.ClearColor);
	RenderCommand::Clear();

	Renderer2D::BeginScene(m_CameraController.GetCamera());

	for (const Ref<GameObject> gameObject : m_GameObjects) { gameObject->Render(); }

	Renderer2D::EndScene();
}

void SandboxScene::OnImGuiRender()
{
	HL_PROFILE_FUNCTION()

	ImGui::SetNextWindowPos(ImVec2(10, 10));
	ImGui::Begin("main",
				 nullptr,
				 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SetWindowFontScale(2.0);
	ImGui::Text("%.0f FPS", ImGui::GetIO().Framerate);
	ImGui::End();
}

// TODO: Move this to the engine
// ReSharper disable once CppMemberFunctionMayBeStatic
void SandboxScene::ReadConfigFile()
{
	HL_PROFILE_FUNCTION()

	Json json;

	std::ifstream input;
	input.open("assets/configs/SandboxConfig.json");
	input >> json;
	input.close();

	Configuration = json.get<SandboxLevelSettings>();
}

void SandboxScene::CreatePyramid(const int pyramidSize)
{
	HL_PROFILE_FUNCTION()

	const auto tileTexture          = Texture2D::Create(Configuration.TileTexture);
	const auto alternateTileTexture = Texture2D::Create(Configuration.AlternateTileTexture);

	for (int q = 0; q < pyramidSize; q++)
	{
		for (int r = 0; r < pyramidSize - q; r++) { m_Grid.insert(Hex(q, r, -q - r)); }
	}

	for (Hex hexagon : m_Grid)
	{
		Ref<Sprite> sprite          = Heirloom::CreateRef<Sprite>();
		Ref<Sprite> alternateSprite = Heirloom::CreateRef<Sprite>();

		sprite->Position     = {HexagonalGrid::HexToPixel(m_HexagonalGridLayout, hexagon), 0.0f};
		sprite->Rotation     = 0.0f;
		sprite->Size         = Configuration.TestTileSpriteSize;
		sprite->Texture      = tileTexture;
		sprite->TilingFactor = 1.0f;
		sprite->TintColor    = glm::vec4(1.0f);

		alternateSprite->Position     = {HexagonalGrid::HexToPixel(m_HexagonalGridLayout, hexagon), 0.0f};
		alternateSprite->Rotation     = 0.0f;
		alternateSprite->Size         = Configuration.TestTileSpriteSize;
		alternateSprite->Texture      = alternateTileTexture;
		alternateSprite->TilingFactor = 1.0f;
		alternateSprite->TintColor    = glm::vec4(1.0f);

		Ref<GameObject> gameObject         = Heirloom::CreateRef<GameObject>(this);
		Ref<SpriteRenderer> spriteRenderer = gameObject->AddComponent(Heirloom::CreateRef<SpriteRenderer>());
		gameObject->
			AddComponent(Heirloom::CreateRef<TileComponent>(hexagon, gameObject, sprite, alternateSprite, true));

		gameObject->GetTransform()->SetPosition({HexagonalGrid::HexToPixel(m_HexagonalGridLayout, hexagon), 0.0f});
		spriteRenderer->SetSprite(sprite);

		m_GameObjects.push_back(gameObject);
	}
}
