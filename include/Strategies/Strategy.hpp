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
        virtual Signal onCandle(const Candle& candle) = 0; 
        virtual std::string_view name() const noexcept = 0;
        virtual void description() const noexcept = 0;
        virtual ~Strategy() = default;
        const std::optional<double>& getRiskPerTrade() const noexcept { return riskPerTrade_; }
        StrategySnapshot getSnapshot() const noexcept { return StrategySnapshot { name(), riskPerTrade_ }; }
        
    protected:
        std::optional<double> riskPerTrade_ = std::nullopt;
    };