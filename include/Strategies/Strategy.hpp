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
    std::optional<double> riskPerTrade;
};

class Strategy {
    public:
        explicit Strategy(std::string_view name = "Strategy") noexcept : kName(name) {}
        virtual Signal onCandle(const Candle& candle) = 0; 
        virtual ~Strategy() = default;
        const std::optional<double>& getRiskPerTrade() const noexcept { return riskPerTrade_; }
        StrategySnapshot getSnapshot() const noexcept { return StrategySnapshot { kName, riskPerTrade_ }; }
        
    protected:
        std::optional<double> riskPerTrade_ = std::nullopt;
        const std::string_view kName;
    };