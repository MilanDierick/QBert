// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#pragma once
#include "Heirloom/Core/Timestep.h"

namespace Heirloom
{
	class GameObject;

	class Component
	{
	public:
		virtual ~Component() = default;

		virtual void Update(Timestep ts) = 0;
		virtual void Render() = 0;

		virtual GameObject* GetParent() const = 0;
		virtual void SetParent(GameObject* gameObject) = 0;
	};
}
