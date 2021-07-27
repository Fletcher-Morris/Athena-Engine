#pragma once

#include <memory>

#include "AthenaCore.h"
#include <spdlog/spdlog.h>

namespace Athena
{
	class ATH_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& MainLogger() { return s_MainLogger; }
		inline static std::shared_ptr<spdlog::logger>& ClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_MainLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}