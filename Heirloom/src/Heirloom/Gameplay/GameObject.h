// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#pragma once
#include <map>
#include "Transform.h"
#include "Components/Component.h"

namespace Heirloom
{
	// TODO: We can only add a single component of each type to a game object, we need to be able to add multiple components per type, fix this
	class GameObject final
	{
	public:
		GameObject()  = default;
		~GameObject() = default;

		// Copy & move operations
		GameObject(const GameObject& other)
			: m_Transform(other.m_Transform), m_Components(other.m_Components)
		{
		}

		GameObject(GameObject&& other) noexcept
			: m_Transform(std::move(other.m_Transform)), m_Components(std::move(other.m_Components))
		{
		}

		GameObject& operator=(const GameObject& other)
		{
			if (this == &other) return *this;
			m_Transform  = other.m_Transform;
			m_Components = other.m_Components;
			return *this;
		}

		GameObject& operator=(GameObject&& other) noexcept
		{
			if (this == &other) return *this;
			m_Transform  = std::move(other.m_Transform);
			m_Components = std::move(other.m_Components);
			return *this;
		}

		// ReSharper disable once CppMemberFunctionMayBeConst
		[[nodiscard]] Ref<Transform> GetTransform() { return m_Transform; }

		void Update(Timestep ts);
		void Render() const;

		template <typename ComponentType = Component>
		Ref<ComponentType> AddComponent(Ref<ComponentType> component);

		template <typename ComponentType = Component>
		[[nodiscard]] Ref<ComponentType> GetComponent();

		template <typename ComponentType = Component>
		bool RemoveComponent(Ref<ComponentType> component);

	private:
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
		// HL_PROFILE_FUNCTION()
		//
		// try { return m_Components.at(typeid(ComponentType)); }
		// catch (std::out_of_range&)
		// {
		// 	HL_CORE_WARN("Tried accessing non-existing component in gameobject!");
		// 	return nullptr;
		// }

		return nullptr;
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
