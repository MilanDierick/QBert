// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#pragma once

#include "spdlog/spdlog.h"

namespace Heirloom
{
	class HL_API Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define HL_CORE_TRACE(...) 	::Heirloom::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HL_CORE_INFO(...) 	::Heirloom::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HL_CORE_WARN(...) 	::Heirloom::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HL_CORE_ERROR(...) 	::Heirloom::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HL_CORE_FATAL(...) 	::Heirloom::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define HL_TRACE(...) 		::Heirloom::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HL_INFO(...) 		::Heirloom::Log::GetClientLogger()->info(__VA_ARGS__)
#define HL_WARN(...) 		::Heirloom::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HL_ERROR(...) 		::Heirloom::Log::GetClientLogger()->error(__VA_ARGS__)
#define HL_FATAL(...) 		::Heirloom::Log::GetClientLogger()->critical(__VA_ARGS__)
