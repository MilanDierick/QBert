#include "hlpch.h"
#include "OpenGLContext.h"

#include "glad/glad.h"

#include "GLFW/glfw3.h"

namespace Heirloom
{
	OpenGLContext::OpenGLContext(GLFWwindow* const windowHandle)
		: m_WindowHandle(windowHandle)
	{
		HL_PROFILE_FUNCTION()

		HL_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		HL_PROFILE_FUNCTION()

		glfwMakeContextCurrent(m_WindowHandle);
		const int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		HL_CORE_ASSERT(status, "Failed to initialize Glad!");

		HL_CORE_INFO("OpenGL Info:");
		HL_CORE_INFO("    Vendor: {0}", glGetString(GL_VENDOR));
		HL_CORE_INFO("    Renderer: {0}", glGetString(GL_RENDERER));
		HL_CORE_INFO("    Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		HL_PROFILE_FUNCTION()

		glfwSwapBuffers(m_WindowHandle);
	}
}
