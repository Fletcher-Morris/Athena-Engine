#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Athena
{
	std::shared_ptr<spdlog::logger> Log::s_EngineLogger;
	std::shared_ptr<spdlog::logger> Log::s_AppLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_EngineLogger = spdlog::stderr_color_mt("Engine");
		s_EngineLogger->set_level(spdlog::level::trace);

		s_AppLogger = spdlog::stderr_color_mt("App");
		s_AppLogger->set_level(spdlog::level::trace);
	}
}