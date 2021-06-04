// ReSharper disable CppUseElementsView
#include "hlpch.h"
#include "GameObject.h"

namespace Heirloom
{
	GameObject::GameObject(Scene* currentScene)
		: m_Active(true), m_CurrentScene(currentScene)
	{
	}

	GameObject::~GameObject()
	{
	}

	GameObject::GameObject(const GameObject& other)
		: m_Active(other.m_Active),
		  m_CurrentScene(other.m_CurrentScene),
		  m_Transform(other.m_Transform),
		  m_Components(other.m_Components)
	{
	}

	GameObject::GameObject(GameObject&& other) noexcept
		: m_Active(other.m_Active),
		  m_CurrentScene(other.m_CurrentScene),
		  m_Transform(std::move(other.m_Transform)),
		  m_Components(std::move(other.m_Components))
	{
	}

	GameObject& GameObject::operator=(const GameObject& other)
	{
		if (this == &other) return *this;
		m_Active     = other.m_Active;
		m_CurrentScene = other.m_CurrentScene;
		m_Transform    = other.m_Transform;
		m_Components   = other.m_Components;
		return *this;
	}

	GameObject& GameObject::operator=(GameObject&& other) noexcept
	{
		if (this == &other) return *this;
		m_Active     = other.m_Active;
		m_CurrentScene = other.m_CurrentScene;
		m_Transform    = std::move(other.m_Transform);
		m_Components   = std::move(other.m_Components);
		return *this;
	}

	void GameObject::Update(const Timestep ts)
	{
		HL_PROFILE_FUNCTION()

		for (auto component : m_Components) component->Update(ts);
	}

	void GameObject::Render() const
	{
		HL_PROFILE_FUNCTION()

		for (auto component : m_Components) component->Render();
	}
}
