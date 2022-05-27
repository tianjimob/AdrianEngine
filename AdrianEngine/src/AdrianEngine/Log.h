#pragma once
#include "Core.h"
#include <memory>
#include <spdlog/spdlog.h>

namespace AdrianEngine {
class AE_API Log {
public:
    static void init();

    static std::shared_ptr<spdlog::logger> getCoreLogger();
    static std::shared_ptr<spdlog::logger> getClientLogger();

private:
    static std::shared_ptr<spdlog::logger> ms_coreLogger;
    static std::shared_ptr<spdlog::logger> ms_clientLogger;
};
} // namespace AdrianEngine

#define AE_CORE_TRACE(...) AdrianEngine::Log::getCoreLogger()->trace(__VA_ARGS__)
#define AE_CORE_INFO(...) AdrianEngine::Log::getCoreLogger()->info(__VA_ARGS__)
#define AE_CORE_WARN(...) AdrianEngine::Log::getCoreLogger()->warn(__VA_ARGS__)
#define AE_CORE_ERROR(...) AdrianEngine::Log::getCoreLogger()->error(__VA_ARGS__)
#define AE_CORE_FATAL(...) AdrianEngine::Log::getCoreLogger()->fatal(__VA_ARGS__)

#define AE_TRACE(...) AdrianEngine::Log::getClientLogger()->trace(__VA_ARGS__)
#define AE_INFO(...) AdrianEngine::Log::getClientLogger()->info(__VA_ARGS__)
#define AE_WARN(...) AdrianEngine::Log::getClientLogger()->warn(__VA_ARGS__)
#define AE_ERROR(...) AdrianEngine::Log::getClientLogger()->error(__VA_ARGS__)
#define AE_FATAL(...) AdrianEngine::Log::getClientLogger()->fatal(__VA_ARGS__)