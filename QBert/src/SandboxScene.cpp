#include "hlpch.h"
#include "SandboxScene.h"

#include "SandboxLevelSettings.h"
#include "Components/HealthComponent.h"
#include "Components/QBertMovementController.h"
#include "HexagonalGrid/HexagonalGrid.h"

#define PYRAMID_WIDTH 7

using Json = nlohmann::json;

SandboxScene::SandboxScene(const std::string& sceneName)
	: Scene(sceneName),
	  m_Configuration(),
	  m_HexagonalGridLayout({ORIENTATION_POINTY, {1.0f, 0.85f}, {0.0f, 0.0f}})
{
	ReadConfigFile();
	m_CameraController = CenteredCameraController(static_cast<float>(m_Configuration.AspectRatioWidth) / static_cast<float>(m_Configuration.AspectRatioHeight));
}

// TODO: Clean this up
void SandboxScene::OnLoad()
{
	HL_INFO("Loading SandboxScene...");

	const auto qbert1Texture = Heirloom::Texture2D::Create(m_Configuration.QBertTexture);

	const auto qbertSprite = Heirloom::CreateRef<Heirloom::Sprite>(
		Heirloom::Sprite(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f), 0.0f, qbert1Texture, 1.0f, glm::vec4(1.0f)));
	auto qbertGameObject      = Heirloom::CreateRef<Heirloom::GameObject>();
	auto qbertSpriteRenderer  = qbertGameObject->AddComponent(Heirloom::CreateRef<Heirloom::SpriteRenderer>());
	auto qbertHealthComponent = qbertGameObject->AddComponent(
		Heirloom::CreateRef<HealthComponent>(m_Configuration.MaximumHealth, m_Configuration.StartHealth));

	qbertSpriteRenderer->SetSprite(qbertSprite);
	auto movementController = qbertGameObject->AddComponent(Heirloom::CreateRef<QBertMovementController>(
		m_Configuration.TicksBetweenMoves,
		m_Configuration.TicksPerMove,
		Hex(static_cast<int>(m_Configuration.InitialQBertPosition.x),
			static_cast<int>(m_Configuration.InitialQBertPosition.y),
			-static_cast<int>(m_Configuration.InitialQBertPosition.z)),
		Heirloom::CreateRef<std::unordered_set<Hex>>(m_Grid)));

	movementController->SetSpriteRenderer(qbertSpriteRenderer);
	qbertHealthComponent->RegisterOutOfBoundsEventHandler(movementController);

	CreatePyramid(m_Configuration.PyramidWidth);

	// This mess is to center the pyramid in the viewport, can this be made easier?
	const Hex hex = *m_Grid.find(Hex(static_cast<int>(m_Configuration.CameraHexPosition.x),
									 static_cast<int>(m_Configuration.CameraHexPosition.y),
									 static_cast<int>(m_Configuration.CameraHexPosition.z)));
	glm::vec3 finalCameraPosition = glm::vec3(HexagonalGrid::HexToPixel(m_HexagonalGridLayout, hex), 0.0f) + glm::vec3(
		m_HexagonalGridLayout.Size.x,
		-m_HexagonalGridLayout.Size.y / 2,
		0.0f);
	m_CameraController.SetCameraPosition(finalCameraPosition);
	m_CameraController.SetZoomLevel(m_Configuration.InitialZoomLevel);

	m_GameObjects.push_back(qbertGameObject);
}

void SandboxScene::OnUnload()
{
	HL_INFO("Unloading SandboxScene...");
}

void SandboxScene::OnUpdate()
{
	HL_PROFILE_FUNCTION()

	for (const Heirloom::Ref<Heirloom::GameObject> gameObject : m_GameObjects)
	{
		gameObject->Update(Heirloom::Timestep{0.016f});
	}
}

void SandboxScene::OnRender()
{
	Heirloom::RenderCommand::SetClearColor(m_Configuration.ClearColor);
	Heirloom::RenderCommand::Clear();

	Heirloom::Renderer2D::BeginScene(m_CameraController.GetCamera());

	for (const Heirloom::Ref<Heirloom::GameObject> gameObject : m_GameObjects) { gameObject->Render(); }

	Heirloom::Renderer2D::EndScene();
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
void SandboxScene::ReadConfigFile()
{
	Json json;

	std::ifstream input;
	input.open("assets/configs/SandboxConfig.json");
	input >> json;
	input.close();

	m_Configuration = json.get<SandboxLevelSettings>();
}

void SandboxScene::CreatePyramid(const int pyramidSize)
{
	const auto testTileTexture = Heirloom::Texture2D::Create(m_Configuration.TestTileTexture);

	for (int q = 0; q < pyramidSize; q++)
	{
		for (int r = 0; r < pyramidSize - q; r++) { m_Grid.insert(Hex(q, r, -q - r)); }
	}

	for (Hex hexagon : m_Grid)
	{
		Heirloom::Ref<Heirloom::GameObject> gameObject         = Heirloom::CreateRef<Heirloom::GameObject>();
		Heirloom::Ref<Heirloom::SpriteRenderer> spriteRenderer = gameObject->AddComponent(
			Heirloom::CreateRef<Heirloom::SpriteRenderer>());
		Heirloom::Ref<Heirloom::Sprite> sprite = Heirloom::CreateRef<Heirloom::Sprite>();

		sprite->Position     = {HexagonalGrid::HexToPixel(m_HexagonalGridLayout, hexagon), 0.0f};
		sprite->Rotation     = 0.0f;
		sprite->Size         = m_Configuration.TestTileSpriteSize;
		sprite->Texture      = testTileTexture;
		sprite->TilingFactor = 1.0f;
		sprite->TintColor    = glm::vec4(1.0f);

		spriteRenderer->SetSprite(sprite);

		m_GameObjects.push_back(gameObject);
	}
}
