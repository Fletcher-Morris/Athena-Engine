#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Athena
{
	std::shared_ptr<spdlog::logger> Log::s_MainLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_MainLogger = spdlog::stderr_color_mt("AthenaEngine");
		s_MainLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stderr_color_mt("Application");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}