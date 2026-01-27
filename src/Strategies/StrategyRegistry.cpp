#include "Strategies/StrategyRegistry.hpp"

#include <algorithm>
#include <ranges>

std::unique_ptr<Strategy> StrategyRegistry::CreateStrategy(std::string_view strategyName) {
    std::unique_ptr<Strategy> strategy = nullptr;
    auto it = StrategyMap().find(strategyName);

    if(it != StrategyMap().end())
        strategy = it->second();
    
    return strategy;
}

const std::vector<std::string_view>& StrategyRegistry::StrategyNames() {
    static std::vector<std::string_view> kStrategyNames;
    if(kStrategyNames.empty()) {
        kStrategyNames.reserve(StrategyMap().size());
        for(const auto& [name, _]: StrategyMap())
            kStrategyNames.push_back(name);
    }
    
    return kStrategyNames;
}

const std::unordered_map<std::string_view, std::function<std::unique_ptr<Strategy>()>>& StrategyRegistry::StrategyMap() {
    static const std::unordered_map<std::string_view, std::function<std::unique_ptr<Strategy>()>> kStrategyMap = {
        { StrategySMA::Name(), []{ return std::make_unique<StrategySMA>(); } },
        { StrategyEngulfing::Name(), []{ return std::make_unique<StrategyEngulfing>(); } }
    };
    
    return kStrategyMap;
}