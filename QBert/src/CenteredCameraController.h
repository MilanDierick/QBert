// Author: Milan Dierick
// Created: 02/06/2021 2:36 AM
// Solution: QBert

#pragma once
#include "Heirloom/Events/ApplicationEventArgs.h"
#include "Heirloom/Events/MouseEventArgs.h"
#include "Heirloom/Renderer/OrthographicCamera.h"

class CenteredCameraController
{
public:
	explicit CenteredCameraController(float aspectRatio);

	Heirloom::OrthographicCamera& GetCamera() { return m_Camera; }
	const Heirloom::OrthographicCamera& GetCamera() const { return m_Camera; }
	float GetZoomLevel() const { return m_ZoomLevel; }
	void SetZoomLevel(float zoomLevel);
	void SetCameraPosition(glm::vec3& position) { m_Camera.SetPosition(position); }

private:
	void OnMouseScrolledEvent(Heirloom::MouseScrolledEventArgs eventArgs);
	void OnWindowResizedEvent(Heirloom::WindowResizedEventArgs eventArgs);
	float m_AspectRatio;
	float m_ZoomLevel = 1.0f;
	Heirloom::OrthographicCamera m_Camera;
};
