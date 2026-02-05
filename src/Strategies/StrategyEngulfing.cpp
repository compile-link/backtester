#include "Strategies/StrategyEngulfing.hpp"

#include <iostream>

Signal StrategyEngulfing::onCandle(const Candle& candle) {
    Signal signal = Signal::Wait;
    if(strongMove_.isComplete() && strongMove_.isEngulfing(candle)) {
        switch (strongMove_.direction) {
            case MoveDirection::Bull: 
                signal = Signal::Sell;
                break;
            case MoveDirection::Bear: 
                signal = Signal::Buy;
                break;
            default:
                signal = Signal::Wait;
                break;
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
    const Candle& prev = candles.back();

    MoveDirection candleDirection = (candle.open < candle.close) ? MoveDirection::Bull : MoveDirection::Bear;   
    
    if(candleDirection == this->direction) return false;

    bool isEngulfing = (candle.open <= prev.close && candle.close >= prev.open) ||
                       (candle.open >= prev.close && candle.close <= prev.open);
        
    return isEngulfing;
}
