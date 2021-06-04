// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#pragma once
#include <map>
#include "Transform.h"
#include "Components/Component.h"
#include "Heirloom/Scenes/Scene.h"

namespace Heirloom
{
	// TODO: We can only add a single component of each type to a game object, we need to be able to add multiple components per type, fix this
	class GameObject final
	{
	public:
		explicit GameObject(Scene* currentScene);
		~GameObject();

		// Copy & move operations
		GameObject(const GameObject& other);
		GameObject(GameObject&& other) noexcept;
		GameObject& operator=(const GameObject& other);
		GameObject& operator=(GameObject&& other) noexcept;

		// ReSharper disable once CppMemberFunctionMayBeConst
		[[nodiscard]] Ref<Transform> GetTransform() { return m_Transform; }
		[[nodiscard]] Scene* GetCurrentScene() const { return m_CurrentScene; }
		[[nodiscard]] bool IsActive() const { return m_Active; }
		void SetActive(const bool isActive) { m_Active = isActive; }
		
		void Update(Timestep ts);
		void Render() const;

		template <typename ComponentType = Component>
		Ref<ComponentType> AddComponent(Ref<ComponentType> component);

		template <typename ComponentType = Component>
		[[nodiscard]] Ref<ComponentType> GetComponent();

		template <typename ComponentType = Component>
		bool RemoveComponent(Ref<ComponentType> component);

	private:
		bool m_Active;
		Scene* m_CurrentScene{nullptr};
		Ref<Transform> m_Transform{CreateRef<Transform>(this)};
		std::vector<Ref<Component>> m_Components;
	};

	template <typename ComponentType>
	Ref<ComponentType> GameObject::AddComponent(Ref<ComponentType> component)
	{
		HL_PROFILE_FUNCTION()

		component->SetParent(this);
		m_Components.push_back(component);

		return component;
	}

	template <typename ComponentType>
	Ref<ComponentType> GameObject::GetComponent()
	{
		for (std::shared_ptr<Component> component : m_Components)
		{
			Ref<ComponentType> castedType = std::dynamic_pointer_cast<ComponentType>(component);

			if (castedType)
			{
				return castedType;
			}
		}

		return Ref<ComponentType>(nullptr);
	}

	template <typename ComponentType>
	bool GameObject::RemoveComponent(Ref<ComponentType> component)
	{
		// HL_PROFILE_FUNCTION()
		//
		// HL_CORE_TRACE("Removed component of type {0} from game object", typeid(ComponentType));
		// return m_Components.erase(typeid(component));

		return false;
	}
}
