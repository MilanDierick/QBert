#include "SandboxScene.h"

SandboxScene::SandboxScene(const std::string& sceneName)
	: Scene(sceneName)
{
}

void SandboxScene::OnLoad()
{
	HL_INFO("Loading SandboxScene...");
}

void SandboxScene::OnUnload()
{
	HL_INFO("Unloading SandboxScene...");
}

void SandboxScene::OnUpdate()
{
}

void SandboxScene::OnRender()
{
}

void SandboxScene::OnImGuiRender()
{
}
