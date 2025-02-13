﻿// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#pragma once
#include "Heirloom/Events/ApplicationEventArgs.h"

namespace Heirloom
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		explicit WindowProps(const std::string& title  = "Heirloom Engine",
							 const unsigned int width  = 1280,
							 const unsigned int height = 960)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	/**
	 * \brief Interface representing a desktop system based window
	 */
	class HL_API Window
	{
	public:
		virtual ~Window()
		{
		}

		Event<WindowResizedEventArgs> WindowResizedEvent = Event<WindowResizedEventArgs>();
		Event<WindowClosedEventArgs> WindowClosedEvent   = Event<WindowClosedEventArgs>();

		virtual void OnUpdate() = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}
