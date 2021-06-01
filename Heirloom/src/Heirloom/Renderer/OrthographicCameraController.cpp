#include "hlpch.h"
#include "OrthographicCameraController.h"
#include "Heirloom/Core/Application.h"
#include "Heirloom/Core/Input.h"
#include "Heirloom/Core/KeyCodes.h"

namespace Heirloom
{
	OrthographicCameraController::OrthographicCameraController(const float aspectRatio, const bool rotation)
		: m_AspectRatio(aspectRatio),
		  m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
		  m_Rotation(rotation)
	{
		HL_PROFILE_FUNCTION();

		Input::MouseScrolledEvent += HL_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolledEvent);
		Application::Get().GetWindow().WindowResizedEvent += HL_BIND_EVENT_FN(
			OrthographicCameraController::OnWindowResizedEvent);
	}

	void OrthographicCameraController::Update(const Timestep ts)
	{
		HL_PROFILE_FUNCTION()

		if (Input::IsKeyPressed(HL_KEY_A))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(HL_KEY_D))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(HL_KEY_W))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(HL_KEY_S))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(HL_KEY_Q)) m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Input::IsKeyPressed(HL_KEY_E)) m_CameraRotation -= m_CameraRotationSpeed * ts;

			if (m_CameraRotation > 180.0f) m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f) m_CameraRotation += 360.0f;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnMouseScrolledEvent(const MouseScrolledEventArgs eventArgs)
	{
		m_ZoomLevel -= eventArgs.YOffset * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	void OrthographicCameraController::OnWindowResizedEvent(const WindowResizedEventArgs eventArgs)
	{
		m_AspectRatio = static_cast<float>(eventArgs.Width) / static_cast<float>(eventArgs.Height);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}
}
