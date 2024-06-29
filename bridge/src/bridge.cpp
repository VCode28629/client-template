#include "bridge/bridge.h"
#include <cstdlib>

const char *invoke(const char *func, const char *args)
{
    static Project::Bridge::CPP_Bridge bridge;
    auto res = bridge.invoke(func, args);
    char *s = new char[res.size() + 1];
    memcpy(s, res.c_str(), res.size());
    s[res.size()] = '\0';
    return s;
}

void free_str(const char *s) { delete[] s; }

void initialize() { return; }

namespace Project {

namespace Bridge {

void CPP_Bridge::registerFunctions()
{
#define REGISTER_FUNCTION(FUNC, ...) \
    m_funcs[FUNC_NAME(FUNC)] = BridgeFunction{FUNC(), {__VA_ARGS__}}

    REGISTER_FUNCTION(hello, ParamTypeName::String);

#undef REGISTER_FUNCTION
}

Vector<ParamType> CPP_Bridge::parseParams(const Vector<ParamTypeName> &argTypes,
                                          const String &json_list)
{
    return Vector<ParamType>();
}

CPP_Bridge::CPP_Bridge() { registerFunctions(); }

String CPP_Bridge::invoke(String func, String args)
{
    //return m_funcs[func].func(Vector<ParamType>{ParamType(args)}); // TODO: json
}

CallbackFunction CPP_Bridge::hello()
{
    // args: name
    return [](const Vector<ParamType> &args) {
        String name = std::get<String>(args[0]);
        return String("hello ") + name;
    };
}

} // namespace Bridge

} // namespace Project