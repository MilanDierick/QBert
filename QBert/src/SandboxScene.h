// Author: Milan Dierick
// Created: 01/06/2021 7:46 PM
// Solution: QBert

#pragma once
#include <unordered_set>

#include "Heirloom.h"
#include "HexagonalGrid/Hexagon.h"

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
	void DebugHexagonalGrid();

	Heirloom::OrthographicCameraController m_CameraController;
	
	std::unordered_set<Hex> m_Grid;
};
