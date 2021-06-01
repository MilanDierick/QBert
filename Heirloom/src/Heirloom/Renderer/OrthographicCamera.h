// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#pragma once

#include <glm/glm.hpp>

namespace Heirloom
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
		glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }
		glm::vec3& GetPosition() { return m_Position; }
		void SetPosition(const glm::vec3& position);
		float& GetRotation() { return m_Rotation; }
		void SetRotation(float rotation);

	private:
		void RecalculateViewMatrix();

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;
		float m_Rotation = 0.0f;
	};
}
