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
	inline static SandboxLevelSettings Configuration = SandboxLevelSettings();

	explicit SandboxScene(const std::string& sceneName);

	void OnLoad() override;
	void OnUnload() override;
	void OnUpdate() override;
	void OnRender() override;
	void OnImGuiRender() override;

private:
	void ReadConfigFile();

	template <typename T>
	static nlohmann::json ReadFileToJson(std::string fileName);

	void CreatePyramid(int pyramidSize);

	CenteredCameraController m_CameraController;
	Layout m_HexagonalGridLayout;

	std::unordered_set<Hex> m_Grid;
};

template <typename T>
nlohmann::json SandboxScene::ReadFileToJson(const std::string fileName)
{
	HL_PROFILE_FUNCTION()

	nlohmann::json json;

	std::ifstream input;
	input.open(fileName);
	input >> json;
	input.close();

	return json.get<T>();
}
