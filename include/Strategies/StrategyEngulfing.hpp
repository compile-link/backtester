#pragma once

#include "Strategy.hpp"

class StrategyEngulfing : public Strategy {
    public:
        StrategyEngulfing() noexcept {}
        Signal onCandle(const Candle& candle) override; 
        
        // Strategy name on class
        static std::string_view Name() noexcept { return "Engulfing Candle"; } 

        // Strategy name enabling polymorphism
        std::string_view name() const noexcept override { return Name(); } 
};