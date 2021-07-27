#pragma once

#include "AthenaCore.h"
#include <spdlog/spdlog.h>

namespace Athena
{
	class ATH_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& EngineLogger() { return s_EngineLogger; }
		inline static std::shared_ptr<spdlog::logger>& AppLogger() { return s_AppLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_AppLogger;
	};
}

#define ATH_ENGINE_TRACE(...)::Athena::Log::EngineLogger()->trace(__VA_ARGS__)
#define ATH_ENGINE_INFO(...)::Athena::Log::EngineLogger()->info(__VA_ARGS__)
#define ATH_ENGINE_WARN(...)::Athena::Log::EngineLogger()->warn(__VA_ARGS__)
#define ATH_ENGINE_ERROR(...)::Athena::Log::EngineLogger()->error(__VA_ARGS__)
#define ATH_ENGINE_FATAL(...)::Athena::Log::EngineLogger()->fatal(__VA_ARGS__)

#define ATH_TRACE(...)::Athena::Log::AppLogger()->trace(__VA_ARGS__)
#define ATH_INFO(...)::Athena::Log::AppLogger()->info(__VA_ARGS__)
#define ATH_WARN(...)::Athena::Log::AppLogger()->warn(__VA_ARGS__)
#define ATH_ERROR(...)::Athena::Log::AppLogger()->error(__VA_ARGS__)
#define ATH_FATAL(...)::Athena::Log::AppLogger()->fatal(__VA_ARGS__)