// ReSharper disable CppUseElementsView
#include "hlpch.h"
#include "GameObject.h"

namespace Heirloom
{
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
