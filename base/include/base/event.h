#pragma once
#include "./define.h"

C_API void set_func_address(void (*emit_func)(const char *, const char *,
                                              const char *),
                            void (*emit_all_func)(const char *, const char *));

C_API void emit(const char *window_name, const char *event_name,
                const char *json);

C_API void emit_all(const char *event_name, const char *json);
