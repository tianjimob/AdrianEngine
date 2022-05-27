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