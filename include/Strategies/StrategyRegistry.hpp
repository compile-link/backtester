#pragma once

#include "StrategySMA.hpp"
#include "StrategyEngulfing.hpp"
#include "StrategyInfo.hpp"

#include <vector>
#include <string_view>
#include <memory>
#include <unordered_map>

struct StrategyMetadata {
    std::string_view name;
    std::function<void()> description;
    std::function<std::unique_ptr<Strategy>()> create;
};

class StrategyRegistry {
    public:

        static std::unique_ptr<Strategy> createStrategy(std::string_view strategyName); 
        static const std::vector<StrategyInfo>& strategyInfos(); 
        
    private:
        static const std::vector<StrategyMetadata>& strategyMetadataList(); 

        template <typename T>
        static StrategyMetadata makeStrategyMetadata() noexcept; 

};