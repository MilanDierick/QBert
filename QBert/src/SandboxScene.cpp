﻿#include "hlpch.h"
#include "SandboxScene.h"
#include "Components/QBertMovementController.h"
#include "HexagonalGrid/HexagonalGrid.h"
#include "glad/glad.h"

#define PYRAMID_WIDTH 7

SandboxScene::SandboxScene(const std::string& sceneName)
	: Scene(sceneName),
	  m_CameraController(1280.0f / 960.0f),
	  m_HexagonalGridLayout({ORIENTATION_POINTY, {1.0f, 0.85f}, {0.0f, 0.0f}})
{
}

// TODO: Clean this up
void SandboxScene::OnLoad()
{
	HL_INFO("Loading SandboxScene...");

	const auto qbert1Texture = Heirloom::Texture2D::Create("assets/textures/QBert1.png");

	const auto qbertSprite = Heirloom::CreateRef<Heirloom::Sprite>(
		Heirloom::Sprite(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f), 0.0f, qbert1Texture, 1.0f, glm::vec4(1.0f)));
	auto qbertGameObject     = Heirloom::CreateRef<Heirloom::GameObject>();
	auto qbertSpriteRenderer = qbertGameObject->AddComponent(Heirloom::CreateRef<Heirloom::SpriteRenderer>());

	qbertSpriteRenderer->SetSprite(qbertSprite);
	auto movementController = qbertGameObject->AddComponent(
		Heirloom::CreateRef<QBertMovementController>(100,
													 50,
													 Hex(0, 6, -6),
													 Heirloom::CreateRef<std::unordered_set<Hex>>(m_Grid)));

	movementController->SetSpriteRenderer(qbertSpriteRenderer);

	CreatePyramid(PYRAMID_WIDTH);
	
	// This mess is to center the pyramid in the viewport, can this be made easier?
	const Hex hex                 = *m_Grid.find(Hex(1, 4, -5));
	glm::vec3 finalCameraPosition = glm::vec3(HexagonalGrid::HexToPixel(m_HexagonalGridLayout, hex), 0.0f) + glm::vec3(
		m_HexagonalGridLayout.Size.x,
		-m_HexagonalGridLayout.Size.y / 2,
		0.0f);
	m_CameraController.SetCameraPosition(finalCameraPosition);
	m_CameraController.SetZoomLevel(6.0f);

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
	Heirloom::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
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

void SandboxScene::CreatePyramid(const unsigned short int pyramidSize)
{
	const auto testTileTexture = Heirloom::Texture2D::Create("assets/textures/TestTile.png");

	for (int q = 0; q < pyramidSize; q++)
	{
		for (int r = 0; r < pyramidSize - q; r++)
		{
			HL_TRACE("Q: {0} R: {1}", q, r);
			m_Grid.insert(Hex(q, r, -q - r));
		}
	}
	
	for (Hex hexagon : m_Grid)
	{
		Heirloom::Ref<Heirloom::GameObject> gameObject         = Heirloom::CreateRef<Heirloom::GameObject>();
		Heirloom::Ref<Heirloom::SpriteRenderer> spriteRenderer = gameObject->AddComponent(
			Heirloom::CreateRef<Heirloom::SpriteRenderer>());
		Heirloom::Ref<Heirloom::Sprite> sprite = Heirloom::CreateRef<Heirloom::Sprite>();

		sprite->Position     = {HexagonalGrid::HexToPixel(m_HexagonalGridLayout, hexagon), 0.0f};
		sprite->Rotation     = 0.0f;
		sprite->Size         = {1.735f, 1.735f};
		sprite->Texture      = testTileTexture;
		sprite->TilingFactor = 1.0f;
		sprite->TintColor    = glm::vec4(1.0f);

		spriteRenderer->SetSprite(sprite);

		m_GameObjects.push_back(gameObject);
	}
}

void SandboxScene::DebugHexagonalGrid()
{
	for (Hex hexagon : m_Grid)
	{
		std::vector<glm::vec2> points = HexagonalGrid::PolygonCorners(m_HexagonalGridLayout, hexagon);

		glBegin(GL_POLYGON);
		for (glm::vec2 point : points) { glVertex2f(point.x, point.y); }
		glEnd();
	}
}
