#pragma once

#define C_API extern "C" __declspec(dllexport)
#define API __declspec(dllexport)

#define FUNC_NAME(x) #x