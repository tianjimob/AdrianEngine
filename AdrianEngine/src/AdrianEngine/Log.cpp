#include "aepch.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace AdrianEngine {

std::shared_ptr<spdlog::logger> Log::ms_coreLogger;
std::shared_ptr<spdlog::logger> Log::ms_clientLogger;

void Log::init() {
  spdlog::set_pattern("%^[%T] %n: %v%$");
  ms_coreLogger = spdlog::stdout_color_mt("AdrianEngine");
  ms_coreLogger->set_level(spdlog::level::trace);
  ms_clientLogger = spdlog::stdout_color_mt("App");
  ms_clientLogger->set_level(spdlog::level::trace);
}

inline std::shared_ptr<spdlog::logger> Log::getCoreLogger() {
  return ms_coreLogger;
}

inline std::shared_ptr<spdlog::logger> Log::getClientLogger() {
  return ms_clientLogger;
}

} // namespace AdrianEngine
