// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#pragma once

#include "Components/Component.h"
#include "glm/vec3.hpp"

namespace Heirloom
{
	class Transform final : Component
	{
	public:
		Transform();
		Transform(glm::vec3 position, glm::vec3 scale);

		[[nodiscard]] const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
		void SetPosition(glm::vec3 position);
		[[nodiscard]] const glm::vec3& GetScale() const { return m_Scale; }
		void SetScale(float x, float y, float z);
		void SetScale(glm::vec3 scale);

		void Update(Timestep ts) override;
		void Render() override;

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Scale;
	};
}
