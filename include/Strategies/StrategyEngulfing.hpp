#pragma once

#include "Strategy.hpp"

class StrategyEngulfing : public Strategy {
    public:
        StrategyEngulfing() noexcept {}
        Signal onCandle(const Candle& candle) override; 
        
        // Strategy name enabling polymorphism
        std::string_view name() const noexcept override { return staticName(); } 

        // Strategy name can be called on class
        static std::string_view staticName() noexcept { return "Engulfing Candle"; } 
        
        // Strategy description enabling polymorphism
        void description() const noexcept override { return staticDescription(); };

        // Strategy description can be called on class
        static void staticDescription() noexcept;
};