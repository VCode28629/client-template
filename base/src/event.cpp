#include "base/event.h"

void (*emit_func)(const char *window_name, const char *event_name,
                  const char *json);
void (*emit_all_func)(const char *window_name, const char *json);

void set_func_address(void (*emit_func_address)(const char *, const char *,
                                                const char *),
                      void (*emit_all_func_address)(const char *, const char *))
{
    emit_func = emit_func_address;
    emit_all_func = emit_all_func_address;
}

void emit(const char *window_name, const char *event_name, const char *json)
{
    emit_func(window_name, event_name, json);
}

void emit_all(const char *event_name, const char *json)
{
    emit_all_func(event_name, json);
}