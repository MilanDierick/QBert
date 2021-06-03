// Author: Milan Dierick
// Created: 01/06/2021 7:46 PM
// Solution: QBert

#pragma once
#include <unordered_set>

#include "CenteredCameraController.h"
#include "Heirloom.h"
#include "SandboxLevelSettings.h"
#include "HexagonalGrid/Hexagon.h"
#include "HexagonalGrid/Layout.h"

class SandboxScene final : public Heirloom::Scene
{
public:
	explicit SandboxScene(const std::string& sceneName);

	void OnLoad() override;
	void OnUnload() override;
	void OnUpdate() override;
	void OnRender() override;
	void OnImGuiRender() override;

private:
	void ReadConfigFile();
	void CreatePyramid(const int pyramidSize);

	SandboxLevelSettings m_Configuration;

	CenteredCameraController m_CameraController;
	Layout m_HexagonalGridLayout;
	
	std::unordered_set<Hex> m_Grid;
};
