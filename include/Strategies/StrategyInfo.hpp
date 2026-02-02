#pragma once

#include <string_view>
#include <functional>

struct StrategyInfo {
    std::string_view name;
    std::function<void()> description;
};
