#include "Strategies/StrategyEngulfing.hpp"

Signal StrategyEngulfing::onCandle(const Candle& candle) {
    return Signal::Wait;
} 