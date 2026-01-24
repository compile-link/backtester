#pragma once

#include "Strategy.hpp"

class StrategyEngulfing : public Strategy {
    public:
        StrategyEngulfing() noexcept: Strategy("Engulfing Candle") {}
        Signal onCandle(const Candle& candle) override; 
}