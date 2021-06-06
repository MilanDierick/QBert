#include "hlpch.h"
#include "CenteredCameraController.h"

#include "Heirloom/Core/Application.h"
#include "Heirloom/Core/Input.h"

CenteredCameraController::CenteredCameraController(const float aspectRatio)
	: m_AspectRatio(aspectRatio),
	  m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
{
	HL_PROFILE_FUNCTION();

	Heirloom::Application::Get().GetWindow().WindowResizedEvent += HL_BIND_EVENT_FN(
		CenteredCameraController::OnWindowResizedEvent);
}

void CenteredCameraController::SetZoomLevel(const float zoomLevel)
{
	m_ZoomLevel = zoomLevel;
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
}

void CenteredCameraController::OnWindowResizedEvent(const Heirloom::WindowResizedEventArgs eventArgs)
{
	m_AspectRatio = static_cast<float>(eventArgs.Width) / static_cast<float>(eventArgs.Height);
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
}
