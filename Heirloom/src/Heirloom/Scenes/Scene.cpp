#include "hlpch.h"
#include "Scene.h"

namespace Heirloom
{
	Scene::Scene(const std::string sceneName)
		: m_IsActive(false), m_SceneName(sceneName)
	{
	}

	bool Scene::IsActive() const { return m_IsActive; }

	void Scene::SetActive(const bool active) { m_IsActive = active; }

	std::string Scene::GetName() const { return m_SceneName; }
}
