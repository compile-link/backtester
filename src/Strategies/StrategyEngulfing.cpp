#include "Strategies/StrategyEngulfing.hpp"

#include <iostream>
#include <algorithm>

Signal StrategyEngulfing::onCandle(const Candle& candle, std::optional<double>& stopLoss) {
    Signal signal = Signal::Wait;
    if(strongMove_.isComplete() && strongMove_.isEngulfing(candle)) {
        switch (strongMove_.direction) {
            case MoveDirection::Bull: {
                signal = Signal::Sell;
                auto it = std::max_element(strongMove_.candles.begin(), strongMove_.candles.end(),
                            [](const Candle& a, const Candle& b) { return a.high < b.high; });
                stopLoss = std::max(it->high, candle.high);
                break;
            }
            case MoveDirection::Bear: { 
                signal = Signal::Buy;
                auto it = std::min_element(strongMove_.candles.begin(), strongMove_.candles.end(),
                            [](const Candle& a, const Candle& b) { return a.low < b.low; });
                stopLoss = std::min(it->low, candle.low);
                break;
            }
            default: {
                signal = Signal::Wait;
                break;
            }
        }
    };

    strongMove_.update(candle);

    return signal;
} 

void StrategyEngulfing::staticDescription() noexcept {
    std::cout << "Looks for strong moves in one direction followed by an engulfing candle in the opposite direction.\n\
Buy signal: bullish engulfing candle.\n\
Sell signal: bearish engulfing candle.\n";
} 

void StrongMove::update(const Candle& candle) {
    if (candle.open == candle.close) return;
    MoveDirection candleDirection = (candle.open < candle.close) ? MoveDirection::Bull : MoveDirection::Bear;   

    if (candles.empty()) {
        this->direction = candleDirection;
    };

    if (this->direction != candleDirection) {
        candles.clear();
        this->direction = candleDirection;
    };

    candles.push_back(candle);
}

bool StrongMove::isEngulfing(const Candle& candle) const noexcept {
    if (candles.empty()) return false;
    if (candle.open == candle.close) return false;

    const Candle& prev = candles.back();

    MoveDirection candleDirection = (candle.open < candle.close) ? MoveDirection::Bull : MoveDirection::Bear;   
    
    if(candleDirection == this->direction) return false;

    bool isEngulfing = (candleDirection == MoveDirection::Bull && candle.open <= prev.close && candle.close > prev.open) ||
                       (candleDirection == MoveDirection::Bear && candle.open >= prev.close && candle.close < prev.open);
        
    return isEngulfing;
}
