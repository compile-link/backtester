
#include "StrategySMA.hpp"
#include <iostream>

StrategySMA::StrategySMA(std::function<void (const Event&)> callback, size_t p): Strategy(callback), period_(p) {
    notify_(StrategyEvent {kName}); 
}

Signal StrategySMA::onCandle(const Candle& candle) {

    Signal signal = Signal::Wait;
    updateSMA(candle);

    if(sma_ < 0.0) return signal;

    CandleCloseSide currCloseSide = 
        (candle.close - sma_ > 0.0) ? CandleCloseSide::BuySide : CandleCloseSide::SellSide; 
    
    if (currCloseSide != prevCloseSide_) {
        signal = (currCloseSide == CandleCloseSide::BuySide) ? Signal::Buy : Signal::Sell;   
    }

    prevCloseSide_ = currCloseSide; 
    return signal;
}

void StrategySMA::updateSMA(const Candle& candle){
    smaPoints_.push_back(candle.close);
    if(smaPoints_.size() < period_)
        return;

    if(smaPoints_.size() > period_)
        smaPoints_.erase(smaPoints_.begin());
    
    double sum = 0.0;
    for(const auto& point : smaPoints_)
        sum += point;
    
    sma_ = sum / period_;
}