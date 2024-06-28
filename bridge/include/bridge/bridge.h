#pragma once

#include "base/base.h"
#include <functional>
#include <variant>

namespace Project {

namespace Bridge {

using ParamType = std::variant<int, double, String, bool>;
using ReturnType = std::function<String(const Vector<ParamType> &)>;

class CPP_Bridge
{
private:
    void registerFunctions();
    ReturnType hello();

public:
    CPP_Bridge();
    String invoke(String func, String args);

private:
    HashMap<StringView, ReturnType> m_funcs;
};

} // namespace Bridge

} // namespace Project

C_API const char *invoke(const char *func, const char *args);

C_API void initialize();

C_API void free_str(const char *s);