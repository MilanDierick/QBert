#include "hlpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Heirloom
{
	OrthographicCamera::OrthographicCamera(const float left, const float right, const float bottom, const float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
		  m_ViewMatrix(1.0f),
		  m_ViewProjectionMatrix(m_ProjectionMatrix * m_ViewMatrix),
		  m_Position(0.0f)
	{
	}

	void OrthographicCamera::SetProjection(const float left, const float right, const float bottom, const float top)
	{
		HL_PROFILE_FUNCTION()

		m_ProjectionMatrix     = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		RecalculateViewMatrix();
	}

	void OrthographicCamera::SetRotation(const float rotation)
	{
		m_Rotation = rotation;
		RecalculateViewMatrix();
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		HL_PROFILE_FUNCTION()

		const glm::mat4 transform = translate(glm::mat4(1.0f), m_Position) * rotate(glm::mat4(1.0f),
			glm::radians(m_Rotation),
			glm::vec3(0, 0, 1));

		m_ViewMatrix           = inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
