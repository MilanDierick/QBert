#include "hlpch.h"
#include "SandboxScene.h"

#include "SandboxLevelSettings.h"
#include "Components/CoilyEggMovementController.h"
#include "Components/DiskMovementController.h"
#include "Components/HealthComponent.h"
#include "Components/QBertMovementController.h"
#include "Components/ScoreComponent.h"
#include "Components/TileComponent.h"
#include "Components/UAndWController.h"
#include "HexagonalGrid/HexagonalGrid.h"

#define PYRAMID_WIDTH 7

using Json = nlohmann::json;
using namespace Heirloom;

SandboxScene::SandboxScene(const std::string& sceneName)
	: Scene(sceneName),
	  m_ScoreTemp(0),
	  m_RecreateScene(false),
	  m_CameraController(1280.0f / 960.0f),
	  m_HexagonalGridLayout({ORIENTATION_POINTY, {1.0f, 0.85f}, {0.0f, 0.0f}})
{
	Configuration = ReadFileToJson<SandboxLevelSettings>("assets/configs/SandboxConfig.json");
}

void SandboxScene::OnLoad()
{
	HL_PROFILE_FUNCTION()

	HL_INFO("Loading SandboxScene...");

	InitialiseGameObjectsInScene(0);

	// This mess is to center the pyramid in the viewport, can this be made easier?
	const Hex hex = *m_Grid.find(Hex(static_cast<int>(Configuration.CameraHexPosition.x),
									 static_cast<int>(Configuration.CameraHexPosition.y),
									 static_cast<int>(Configuration.CameraHexPosition.z)));
	glm::vec3 finalCameraPosition = glm::vec3(HexagonalGrid::HexToPixel(m_HexagonalGridLayout, hex), 0.0f);
	m_CameraController.SetCameraPosition(finalCameraPosition);
	m_CameraController.SetZoomLevel(Configuration.InitialZoomLevel);
}

void SandboxScene::OnUnload()
{
	HL_PROFILE_FUNCTION()

	HL_INFO("Unloading SandboxScene...");
}

void SandboxScene::OnUpdate()
{
	HL_PROFILE_FUNCTION()

	++m_RespawnTicks;

	if (m_GameObjects.size() == 0 && m_RecreateScene)
	{
		m_RecreateScene = false;
		InitialiseGameObjectsInScene(m_ScoreTemp);
	}

	if (m_RespawnTicks >= 500)
	{
		SpawnUAndW();
		m_RespawnTicks = 0;
	}

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

void SandboxScene::InitialiseGameObjectsInScene(int currentScore)
{
	CreatePyramid(Configuration.PyramidWidth);

	#pragma region QBertGameObject
	const auto qbert1Texture = Texture2D::Create(Configuration.QBertTexture);

	const auto qbertSprite = Heirloom::CreateRef<Sprite>(qbert1Texture);
	auto qbertGameObject   = Heirloom::CreateRef<GameObject>(this);
	qbertGameObject->GetTransform()->SetParent(qbertGameObject);
	auto qbertSpriteRenderer  = qbertGameObject->AddComponent(Heirloom::CreateRef<SpriteRenderer>());
	auto qbertHealthComponent = qbertGameObject->AddComponent(
		Heirloom::CreateRef<HealthComponent>(Configuration.MaximumHealth, Configuration.StartHealth));

	qbertSpriteRenderer->SetSprite(qbertSprite);

	MovementControllerData qBertData = ReadFileToJson<MovementControllerData>(
		"assets/levels/sandbox/QBertMovementControllerData.json");

	const auto movementController = qbertGameObject->AddComponent(
		Heirloom::CreateRef<QBertMovementController>(qBertData, qbertGameObject));

	movementController->DamageTakenEvent += HL_BIND_EVENT_FN(SandboxScene::OnDamageTakenEvent);

	qbertSpriteRenderer->SetSpriteOffset(glm::vec3{0.0f, m_HexagonalGridLayout.Size.y * 1.25f, -1.0f});

	qbertHealthComponent->RegisterOutOfBoundsEventHandler(movementController);

	m_GameObjects.push_back(qbertGameObject);
	#pragma endregion

	#pragma region DiskGameObject
	MovementControllerData diskData = ReadFileToJson<MovementControllerData>(
		"assets/levels/sandbox/DiskMovementControllerData.json");

	const Ref<Texture2D> diskTexture = Texture2D::Create(Configuration.DiskTexture);

	const Ref<Sprite> diskSprite = CreateRef<Sprite>(diskTexture);

	Ref<GameObject> disk1GameObject         = CreateRef<GameObject>(this);
	Ref<SpriteRenderer> disk1SpriteRenderer = disk1GameObject->AddComponent(CreateRef<SpriteRenderer>());

	disk1SpriteRenderer->SetSprite(diskSprite);

	disk1GameObject->AddComponent(CreateRef<DiskMovementController>(diskData,
																	TileState::Clear,
																	CreateRef<std::unordered_set<Hex>>(m_Grid),
																	disk1GameObject->GetTransform(),
																	disk1GameObject));

	m_GameObjects.push_back(disk1GameObject);
	#pragma endregion

	#pragma region CoilyEggGameObject
	MovementControllerData coilyEggData = ReadFileToJson<MovementControllerData>(
		"assets/levels/sandbox/CoilyEggMovementControllerData.json");

	const auto coilyEggTexture = Texture2D::Create("assets/textures/CoilyEggTexture.png");
	const auto coilyEggSprite  = Heirloom::CreateRef<Sprite>(coilyEggTexture);

	auto coilyEggGameObject = CreateRef<GameObject>(this);

	coilyEggGameObject->AddComponent(
		CreateRef<CoilyEggMovementController>(coilyEggData, TileState::Clear, coilyEggGameObject));

	auto coilyEggSpriteRenderer = coilyEggGameObject->AddComponent(CreateRef<SpriteRenderer>());
	coilyEggSpriteRenderer->SetSprite(coilyEggSprite);
	coilyEggSpriteRenderer->SetSpriteOffset(glm::vec3{0.0f, m_HexagonalGridLayout.Size.y * 1.10f, -1.0f});

	m_GameObjects.push_back(coilyEggGameObject);
	#pragma endregion

	#pragma region ScoreGameObject
	Ref<GameObject> scoreObject = CreateRef<GameObject>(this);
	scoreObject->AddComponent(CreateRef<ScoreComponent>(scoreObject, currentScore));

	m_GameObjects.push_back(scoreObject);
	#pragma endregion
}

void SandboxScene::SpawnUAndW()
{
	const int randomNumber = rand() % 2;

	if (randomNumber == 0)
	{
		#pragma region UAndWControllerETW
		MovementControllerData uAndWETWData = ReadFileToJson<MovementControllerData>(
			"assets/levels/sandbox/UAndWETWMovementControllerData.json");

		const auto uAndWTexture = Texture2D::Create("assets/textures/UAndWTexture.png");
		const auto uAndWSprite  = Heirloom::CreateRef<Sprite>(uAndWTexture);

		auto uAndWETWGameObject = CreateRef<GameObject>(this);

		uAndWETWGameObject->AddComponent(CreateRef<UAndWController>(uAndWETWData,
																	TileState::Clear,
																	UAndWMovementDirection::EastToWest,
																	uAndWETWGameObject));

		auto uAndWETWSpriteRenderer = uAndWETWGameObject->AddComponent(Heirloom::CreateRef<SpriteRenderer>());
		uAndWETWSpriteRenderer->SetSprite(uAndWSprite);
		uAndWETWSpriteRenderer->SetSpriteOffset(glm::vec3{0.0f, m_HexagonalGridLayout.Size.y * 1.10f, -1.0f});

		m_GameObjects.push_back(uAndWETWGameObject);
		#pragma endregion
	}
	else
	{
		#pragma region UAndWControllerWTE
		MovementControllerData uAndWWTEData = ReadFileToJson<MovementControllerData>(
			"assets/levels/sandbox/UAndWWTEMovementControllerData.json");

		const auto uAndWTexture = Texture2D::Create("assets/textures/UAndWTexture.png");
		const auto uAndWSprite  = Heirloom::CreateRef<Sprite>(uAndWTexture);

		auto uAndWETWGameObject = CreateRef<GameObject>(this);

		uAndWETWGameObject->AddComponent(CreateRef<UAndWController>(uAndWWTEData,
																	TileState::Clear,
																	UAndWMovementDirection::WestToEast,
																	uAndWETWGameObject));

		auto uAndWETWSpriteRenderer = uAndWETWGameObject->AddComponent(Heirloom::CreateRef<SpriteRenderer>());
		uAndWETWSpriteRenderer->SetSprite(uAndWSprite);
		uAndWETWSpriteRenderer->SetSpriteOffset(glm::vec3{0.0f, m_HexagonalGridLayout.Size.y * 1.10f, -1.0f});

		m_GameObjects.push_back(uAndWETWGameObject);
		#pragma endregion
	}
}

void SandboxScene::OnDamageTakenEvent(DamageTakenEventArgs args)
{
	UNREFERENCED_PARAMETER(args);

	for (Ref<GameObject> gameObject : m_GameObjects)
	{
		Ref<ScoreComponent> scoreComponent = gameObject->GetComponent<ScoreComponent>();

		if (scoreComponent) { m_ScoreTemp = scoreComponent->GetScore(); }
	}

	for (Ref<GameObject> gameObject : m_GameObjects) { gameObject->SetActive(false); }

	m_RecreateScene = true;
}
