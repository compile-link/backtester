#include "Strategies/StrategyEngulfing.hpp"

#include <iostream>

Signal StrategyEngulfing::onCandle(const Candle& candle) {
    return Signal::Wait;
} 

void StrategyEngulfing::staticDescription() noexcept {
    std::cout << "Looks for strong moves in one direction followed by an engulfing candle in the opposite direction.\n\
Buy signal: bullish engulfing candle.\n\
Sell signal: bearish engulfing candle.\n";
} 