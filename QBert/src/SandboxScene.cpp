#include "SandboxScene.h"

#include "HexagonalGrid/HexagonalGrid.h"
#include "glad/glad.h"

SandboxScene::SandboxScene(const std::string& sceneName)
	: Scene(sceneName), m_CameraController(1280.0f / 960.0f, false)
{
}

void SandboxScene::OnLoad()
{
	HL_INFO("Loading SandboxScene...");

	for (int q = 0; q <= 7; q++) { for (int r = 0; r <= 7 - q; r++) { m_Grid.insert(Hex(q, r, -q - r)); } }
}

void SandboxScene::OnUnload()
{
	HL_INFO("Unloading SandboxScene...");
}

void SandboxScene::OnUpdate()
{
	HL_PROFILE_FUNCTION()

	m_CameraController.Update(Heirloom::Timestep{0.016f});
}

void SandboxScene::OnRender()
{
	Heirloom::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
	Heirloom::RenderCommand::Clear();

	Heirloom::Renderer2D::BeginScene(m_CameraController.GetCamera());

	DebugHexagonalGrid();
	
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

void SandboxScene::DebugHexagonalGrid()
{
	const Layout layout = Layout(ORIENTATION_POINTY, {0.5f, 0.5f}, {0.0f, 0.0f});

	for (Hex hexagon : m_Grid)
	{
		std::vector<glm::vec2> points = HexagonalGrid::PolygonCorners(layout, hexagon);

		glBegin(GL_POLYGON);
		for (glm::vec2 point : points) { glVertex2f(point.x, point.y); }
		glEnd();
	}
}
