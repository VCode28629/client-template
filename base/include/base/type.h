#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <nlohmann/json.hpp>

namespace Project {

namespace stl = std;

using String = stl::string;
using StringView = stl::string_view;

template <typename T>
using Vector = stl::vector<T>;
template <typename K, typename V>
using HashMap = stl::unordered_map<K, V>;

using json = nlohmann::json;

} // namespace Project
