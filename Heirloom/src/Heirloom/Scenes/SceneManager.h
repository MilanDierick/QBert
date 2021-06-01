// Author: Milan Dierick
// Created: 11/04/2021 6:23 PM
// Solution: HeirloomEngine

#pragma once

#include <future>

namespace Heirloom
{
	class Scene;
	class Layer;

	class SceneManager
	{
	public:
		static bool LoadScene(Scene* newScene, bool cacheCurrentScene = false);
		static void RemoveAllScenes();

		static void Update();
		static void Render();
		static void ImGuiRender();

	private:
		static void SetActiveScene(Scene* newScene);
		static bool RemoveScene(std::string sceneName);

		static Scene* m_ActiveScene;
		static std::vector<Scene*> m_SceneCache;
	};
}
