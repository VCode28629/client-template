#pragma once

#include "base/base.h"
#include <functional>
#include <variant>
#include <cstdint>

namespace Project {

namespace Bridge {

using ParamType =
    std::variant<int32_t, uint32_t, int64_t, uint64_t, double, String, bool>;
using CallbackFunction = std::function<String(const Vector<ParamType> &)>;
enum class ParamTypeName : uint8_t
{
    Int32,
    Uint32,
    Int64,
    Uint64,
    Double,
    String,
    Bool,
    JsonObject
};

struct BridgeFunction
{
    CallbackFunction func;
    Vector<ParamTypeName> argTypes;
};

class CPP_Bridge
{
private:
    void registerFunctions();
    Vector<ParamType> parseParams(const Vector<ParamTypeName> &argTypes,
                                  const String &json_list);

    // Callback functions
    CallbackFunction hello();

public:
    CPP_Bridge();
    String invoke(String func, String args);

private:
    HashMap<StringView, BridgeFunction> m_funcs;
};

} // namespace Bridge

} // namespace Project

C_API const char *invoke(const char *func, const char *args);

C_API void initialize();

C_API void free_str(const char *s);

C_API void emit_init(void (*emit_func)(const char *, const char *,
                                       const char *),
                     void (*emit_all_func)(const char *, const char *));