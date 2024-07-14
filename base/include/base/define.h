#pragma once

#ifdef _WIN32
#define C_API extern "C" __declspec(dllexport)
#define API __declspec(dllexport)
#else
#define C_API extern "C" __attribute__((visibility("default")))
#define API __attribute__((visibility("default")))
#endif

#define FUNC_NAME(x) #x