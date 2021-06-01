#include "hlpch.h"
#include "SceneManager.h"

#include "Scene.h"

namespace Heirloom
{
	Scene* SceneManager::m_ActiveScene             = nullptr;
	std::vector<Scene*> SceneManager::m_SceneCache = std::vector<Scene*>();

	bool SceneManager::LoadScene(Scene* newScene, const bool cacheCurrentScene)
	{
		HL_PROFILE_FUNCTION()

		if (!cacheCurrentScene && m_ActiveScene != nullptr) { RemoveScene(newScene->GetName()); }

		m_SceneCache.push_back(newScene);
		SetActiveScene(newScene);
		m_ActiveScene->OnLoad();
		return true;
	}

	void SceneManager::RemoveAllScenes() { for (Scene* scene : m_SceneCache) { RemoveScene(scene->GetName()); } }

	void SceneManager::Update()
	{
		HL_PROFILE_FUNCTION()

		for (Scene* scene : m_SceneCache) { scene->OnUpdate(); }
	}

	void SceneManager::Render()
	{
		HL_PROFILE_FUNCTION()

		for (Scene* scene : m_SceneCache) { scene->OnRender(); }
	}

	void SceneManager::ImGuiRender()
	{
		HL_PROFILE_FUNCTION()

		for (Scene* scene : m_SceneCache) { scene->OnImGuiRender(); }
	}

	void SceneManager::SetActiveScene(Scene* newScene)
	{
		HL_PROFILE_FUNCTION()

		if (m_ActiveScene != nullptr) { m_ActiveScene->SetActive(false); }

		m_ActiveScene = newScene;
		m_ActiveScene->SetActive(true);
	}

	bool SceneManager::RemoveScene(const std::string sceneName)
	{
		HL_PROFILE_FUNCTION()

		const std::vector<Scene*>::iterator it = std::ranges::find_if(m_SceneCache,
																	  [=](Scene* scene)
																	  {
																		  return scene->GetName() == sceneName;
																	  });

		if (it == std::end(m_SceneCache))
		{
			HL_CORE_ERROR("Scene with name {0} designated to be removed could not be found!", sceneName);
			return false;
		}

		(*it)->OnUnload();
		delete *it;
		m_SceneCache.erase(it);
		return true;
	}
}
