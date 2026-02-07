#pragma once

#include "Candle.hpp"

#include <functional>
#include <optional>

enum class Signal {
    Buy,
    Sell,
    Wait
};

struct StrategySnapshot {
    std::string_view strategyName;
    std::optional<double> riskReward;
};

class Strategy {
    public:
        Strategy(std::optional<double> rr = std::nullopt): kRiskReward(rr) {}
        virtual Signal onCandle(const Candle& candle, std::optional<double>& stopLoss) = 0; 
        virtual std::string_view name() const noexcept = 0;
        virtual void description() const noexcept = 0;
        const std::optional<double>& getRiskReward() const noexcept { return kRiskReward; }
        StrategySnapshot getSnapshot() const noexcept { return StrategySnapshot { name(), kRiskReward }; }

        virtual ~Strategy() = default;
        
    protected:
        const std::optional<double> kRiskReward = std::nullopt;
    };