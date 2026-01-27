#pragma once

#include "StrategySMA.hpp"
#include "StrategyEngulfing.hpp"

#include <vector>
#include <string_view>
#include <memory>
#include <unordered_map>

class StrategyRegistry {
    public:
        static std::unique_ptr<Strategy> CreateStrategy(std::string_view strategyName); 
        static const std::vector<std::string_view>& StrategyNames(); 
        
    private:
        static const std::unordered_map<std::string_view, std::function<std::unique_ptr<Strategy>()>>& StrategyMap();

};