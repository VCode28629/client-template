#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace Project {

namespace stl = std;

using String = stl::string;
using StringView = stl::string_view;

template <typename T>
using Vector = stl::vector<T>;
template <typename K, typename V>
using HashMap = stl::unordered_map<K, V>;

} // namespace Project
