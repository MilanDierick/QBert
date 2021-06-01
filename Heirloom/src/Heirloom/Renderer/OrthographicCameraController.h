// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#pragma once
#include "Heirloom/Core/Timestep.h"
#include "Heirloom/Events/ApplicationEventArgs.h"
#include "Heirloom/Events/MouseEventArgs.h"
#include "Heirloom/Renderer/OrthographicCamera.h"

namespace Heirloom
{
	class OrthographicCameraController
	{
	public:
		explicit OrthographicCameraController(float aspectRatio, bool rotation = false);

		void Update(Timestep ts);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(const float zoomLevel) { m_ZoomLevel = zoomLevel; }

	private:
		void OnMouseScrolledEvent(MouseScrolledEventArgs eventArgs);
		void OnWindowResizedEvent(WindowResizedEventArgs eventArgs);
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition     = {0.0f, 0.0f, 0.0f};
		float m_CameraRotation         = 0.0f;
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};
}
