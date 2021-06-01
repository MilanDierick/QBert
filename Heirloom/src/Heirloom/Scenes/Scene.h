// Author: Milan Dierick
// Created: 11/04/2021 6:24 PM
// Solution: HeirloomEngine

#pragma once
#include "Heirloom/Gameplay/GameObject.h"

namespace Heirloom
{
	class Layer;

	class Scene
	{
	public:
		explicit Scene(std::string sceneName);
		virtual ~Scene() = default;

		Scene(const Scene& other)                = delete;
		Scene(Scene&& other) noexcept            = delete;
		Scene& operator=(const Scene& other)     = delete;
		Scene& operator=(Scene&& other) noexcept = delete;

		virtual void OnLoad() = 0;
		virtual void OnUnload() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnRender() = 0;
		virtual void OnImGuiRender() = 0;

		bool IsActive() const;
		void SetActive(bool active);
		std::string GetName() const;

	protected:
		bool m_IsActive;
		std::string m_SceneName;
		std::vector<GameObject> m_GameObjects;
	};
}
