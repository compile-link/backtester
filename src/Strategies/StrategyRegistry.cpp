#include "Strategies/StrategyRegistry.hpp"

#include <algorithm>
#include <ranges>

std::unique_ptr<Strategy> StrategyRegistry::createStrategy(std::string_view strategyName) {
    std::unique_ptr<Strategy> strategy = nullptr;
   
    const auto& list = strategyMetadataList();
    auto it = std::find_if(list.begin(), list.end(),
                [strategyName](const auto& strategyMetadata){ return strategyName == strategyMetadata.name; });

    if (it != list.end()) {
        strategy = it->create();
    };

    return strategy;
}

const std::vector<StrategyInfo>& StrategyRegistry::strategyInfos() {
    static std::vector<StrategyInfo> strategyInfos;
    if(strategyInfos.empty()) {
        strategyInfos.reserve(strategyMetadataList().size());
        for(const auto& metadata: strategyMetadataList()) {
            strategyInfos.push_back({metadata.name, metadata.description});
        }
    };
    
    return strategyInfos;
}

const std::vector<StrategyMetadata>& StrategyRegistry::strategyMetadataList() {
    static const std::vector<StrategyMetadata> kStrategyMetadataList = {
        makeStrategyMetadata<StrategySMA>(),
        makeStrategyMetadata<StrategyEngulfing>()
    };
    
    return kStrategyMetadataList;
}

template<typename T>
StrategyMetadata StrategyRegistry::makeStrategyMetadata() noexcept {
    return {
        T::staticName(),
        [](){ T::staticDescription(); },
        [](){ return std::make_unique<T>(); }
    };
}