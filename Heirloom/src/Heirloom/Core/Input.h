// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#pragma once
#include "Heirloom/Events/Event.h"
#include "Heirloom/Events/KeyEventArgs.h"
#include "Heirloom/Events/MouseEventArgs.h"
#include "Heirloom/Core/Core.h"

namespace Heirloom
{
	class HL_API Input
	{
	public:
		virtual ~Input() = default;

		static Event<KeyPressedEventArgs> KeyPressedEvent;
		static Event<KeyReleasedEventArgs> KeyReleasedEvent;
		static Event<KeyTypedEventArgs> KeyTypedEvent;
		static Event<MouseButtonPressedEventArgs> MouseButtonPressedEvent;
		static Event<MouseButtonReleasedEventArgs> MouseButtonReleasedEvent;
		static Event<MouseMovedEventArgs> MouseMovedEvent;
		static Event<MouseScrolledEventArgs> MouseScrolledEvent;

		static bool IsKeyPressed(const int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		static bool IsMouseButtonPressed(const int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual bool GetMouseXImpl() = 0;
		virtual bool GetMouseYImpl() = 0;

	private:
		static Scope<Input> s_Instance;
	};
}
