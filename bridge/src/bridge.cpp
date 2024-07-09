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

void initialize()
{
    using namespace Project;
    // test emit
    stl::thread t([]() {
        while (true)
        {
            emit_all("ping", "pong");
            stl::this_thread::sleep_for(std::chrono::seconds(5));
        }
    });
    t.detach();
    return;
}

void emit_init(void (*emit_func)(const char *, const char *, const char *),
               void (*emit_all_func)(const char *, const char *))
{
    set_func_address(emit_func, emit_all_func);
}

namespace Project {

namespace Bridge {

void CPP_Bridge::registerFunctions()
{
#define REGISTER_FUNCTION(FUNC, ...) \
    m_funcs.try_emplace(FUNC_NAME(FUNC), BridgeFunction{FUNC(), {__VA_ARGS__}})

    REGISTER_FUNCTION(hello, ParamTypeName::String);

#undef REGISTER_FUNCTION
}

Vector<ParamType> CPP_Bridge::parseParams(const Vector<ParamTypeName> &argTypes,
                                          const String &json_list)
{
    json list = json::parse(json_list);
    Vector<ParamType> ret;
    for (int i = 0; i < argTypes.size(); ++i)
    {
        switch (argTypes[i])
        {
            case ParamTypeName::Int32:
                ret.emplace_back(static_cast<int32_t>(list[i]));
                break;
            case ParamTypeName::Uint32:
                ret.emplace_back(static_cast<uint64_t>(list[i]));
                break;
            case ParamTypeName::Int64:
                ret.emplace_back(static_cast<int64_t>(list[i]));
                break;
            case ParamTypeName::Uint64:
                ret.emplace_back(static_cast<uint64_t>(list[i]));
                break;
            case ParamTypeName::Double:
                ret.emplace_back(static_cast<double>(list[i]));
                break;
            case ParamTypeName::String:
                ret.emplace_back(String(list[i]));
                break;
            case ParamTypeName::Bool:
                ret.emplace_back(static_cast<bool>(list[i]));
                break;
            case ParamTypeName::JsonObject:
                ret.emplace_back(String(list[i].dump()));
                break;
        }
    }
    return std::move(ret);
}

CPP_Bridge::CPP_Bridge() { registerFunctions(); }

String CPP_Bridge::invoke(String func, String args)
{
    Vector<ParamType> &&arg_list = parseParams(m_funcs[func].argTypes, args);
    return m_funcs[func].func(arg_list);
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