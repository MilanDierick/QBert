#include "hlpch.h"
#include "WindowsWindow.h"
#include "Heirloom/Core/Input.h"
#include "Heirloom/Events/MouseEventArgs.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Heirloom
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(const int error, const char* description)
	{
		HL_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props) { return new WindowsWindow(props); }

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		HL_PROFILE_FUNCTION()

		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		HL_PROFILE_FUNCTION()

		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		HL_PROFILE_FUNCTION()

		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(const bool enabled)
	{
		if (enabled) glfwSwapInterval(1);
		else glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const { return m_Data.VSync; }

	void WindowsWindow::Init(const WindowProps& props)
	{
		HL_PROFILE_FUNCTION()

		m_Data.Title              = props.Title;
		m_Data.Width              = props.Width;
		m_Data.Height             = props.Height;
		m_Data.WindowResizedEvent = &WindowResizedEvent;
		m_Data.WindowClosedEvent  = &WindowClosedEvent;

		HL_CORE_INFO("Creating window {0} ({1} {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			const int success = glfwInit();
			HL_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(static_cast<int>(props.Width),
									static_cast<int>(props.Height),
									m_Data.Title.c_str(),
									nullptr,
									nullptr);

		m_Context = CreateScope<OpenGLContext>(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window,
								  [](GLFWwindow* window, const int width, const int height)
								  {
									  WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
									  data->Width      = width;
									  data->Height     = height;

									  const WindowResizedEventArgs eventArgs(width, height);
									  data->WindowResizedEvent->Invoke(eventArgs);
								  });

		glfwSetWindowCloseCallback(m_Window,
								   [](GLFWwindow* window)
								   {
									   WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

									   const WindowClosedEventArgs eventArgs;
									   data->WindowClosedEvent->Invoke(eventArgs);
								   });

		glfwSetKeyCallback(m_Window,
						   [](GLFWwindow*, const int key, int, const int action, int)
						   {
							   switch (action)
							   {
								   case GLFW_PRESS:
								   {
									   const KeyPressedEventArgs eventArgs(key, 0);
									   Input::KeyPressedEvent.Invoke(eventArgs);
									   break;
								   }
								   case GLFW_RELEASE:
								   {
									   const KeyReleasedEventArgs eventArgs(key);
									   Input::KeyReleasedEvent.Invoke(eventArgs);
									   break;
								   }
								   case GLFW_REPEAT:
								   {
									   const KeyTypedEventArgs eventArgs(key);
									   Input::KeyTypedEvent.Invoke(eventArgs);
									   break;
								   }
								   default: HL_CORE_ERROR("Tried to process missing GLFW key action");
									   break;
							   }
						   });

		glfwSetCharCallback(m_Window,
							[](GLFWwindow*, const unsigned int keycode)
							{
								const KeyTypedEventArgs eventArgs(keycode);

								Input::KeyTypedEvent.Invoke(eventArgs);
							});

		glfwSetMouseButtonCallback(m_Window,
								   [](GLFWwindow*, const int button, const int action, int)
								   {
									   switch (action)
									   {
										   case GLFW_PRESS:
										   {
											   const MouseButtonPressedEventArgs event(button);
											   Input::MouseButtonPressedEvent.Invoke(event);
											   break;
										   }
										   case GLFW_RELEASE:
										   {
											   const MouseButtonReleasedEventArgs event(button);
											   Input::MouseButtonReleasedEvent.Invoke(event);
											   break;
										   }
										   default: HL_CORE_ERROR("Tried to process missing GLFW key action");
											   break;
									   }
								   });

		glfwSetScrollCallback(m_Window,
							  [](GLFWwindow*, const double xOffset, const double yOffset)
							  {
								  const MouseScrolledEventArgs mouseScrolledEventArgs(static_cast<float>(xOffset),
									  static_cast<float>(yOffset));
								  Input::MouseScrolledEvent.Invoke(mouseScrolledEventArgs);
							  });

		glfwSetCursorPosCallback(m_Window,
								 [](GLFWwindow*, const double xPos, const double yPos)
								 {
									 const MouseMovedEventArgs
										 event(static_cast<float>(xPos), static_cast<float>(yPos));
									 Input::MouseMovedEvent.Invoke(event);
								 });
	}

	void WindowsWindow::Shutdown() const
	{
		HL_PROFILE_FUNCTION()

		glfwDestroyWindow(m_Window);
	}
}
