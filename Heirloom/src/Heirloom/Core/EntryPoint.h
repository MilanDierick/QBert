#pragma once
#include "Heirloom/Profiler/Instrumentation.h"

#ifdef HL_PLATFORM_WINDOWS

extern Heirloom::Application* Heirloom::CreateApplication();

// ReSharper disable once CppNonInlineFunctionDefinitionInHeaderFile
int main()
{
	Heirloom::Log::Init();

	HL_PROFILE_BEGIN_SESSION("Initialization", "HeirloomProfiling-Initialization.json");
	Heirloom::Application* app = Heirloom::CreateApplication();
	HL_PROFILE_END_SESSION();

	try
	{
		HL_PROFILE_BEGIN_SESSION("Runtime", "HeirloomProfiling-Runtime.json");
		app->Run();
		HL_PROFILE_END_SESSION();
	}
	catch (std::exception& exception) { HL_CORE_FATAL(exception.what()); }

	HL_PROFILE_BEGIN_SESSION("Termination", "HeirloomProfiling-Termination.json");
	delete app;
	HL_PROFILE_END_SESSION();

	return EXIT_SUCCESS;
}

#endif
