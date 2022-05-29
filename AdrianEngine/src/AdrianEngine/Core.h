#pragma once

#ifdef AE_PLATFORM_WINDOWS
#ifdef AE_BUILD_DLL
#define AE_API __declspec(dllexport)
#else
#define AE_API __declspec(dllimport)
#endif
#else
#define AE_API
#error AdrianEngine only support Windows!
#endif

#ifdef AE_ENABLE_ASSERTS
#define AE_ASSERT(x, ...)                                                      \
  {                                                                            \
    if (!(x)) {                                                                \
      AE_ERROR("Assertion failed: {0}", __VA_ARGS__);                          \
      __debugbreak();                                                          \
    }                                                                          \
  }
#define AE_CORE_ASSERT(x, ...)                                                 \
  {                                                                            \
    if (!(x)) {                                                                \
      AE_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__);                     \
      __debugbreak();                                                          \
    }                                                                          \
  }
#else
#define AE_ASSERT(x, ...)
#define AE_CORE_ASSERT(x, ...)
#endif

constexpr int bitLShift(int x) { return 1 << x; }