#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"

namespace Sheff {

	class SHEFF_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

}


#define SH_CORE_TRACE(...)	::Sheff::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SH_CORE_INFO(...)	::Sheff::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SH_CORE_WARN(...)	::Sheff::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SH_CORE_ERROR(...)	::Sheff::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SH_CORE_FATAL(...)	::Sheff::Log::GetCoreLogger()->fatal(__VA_ARGS__)
										 
#define SH_TRACE(...)		::Sheff::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SH_INFO(...)		::Sheff::Log::GetClientLogger()->info(__VA_ARGS__)
#define SH_WARN(...)		::Sheff::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SH_ERROR(...)		::Sheff::Log::GetClientLogger()->error(__VA_ARGS__)
#define SH_FATAL(...)		::Sheff::Log::GetClientLogger()->fatal(__VA_ARGS__)