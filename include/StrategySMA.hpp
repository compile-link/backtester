
#pragma once

#include "Strategy.hpp"
#include <vector>

enum class CandleCloseSide {
    BuySide,
    SellSide,
    Uninitialized
};

class StrategySMA: public Strategy {
    public:
        explicit StrategySMA(std::function<void (const Event&)> callback, size_t p = kDefaultPeriod);

        Signal onCandle(const Candle& candle) override; 

    private:
        static constexpr std::string_view kName = "Simple Moving Average (SMA)";
        static constexpr size_t kDefaultPeriod = 14;
        size_t period_ = 0;
        std::vector<double> smaPoints_; 
        double sma_ = 0;
        CandleCloseSide prevCloseSide_ = CandleCloseSide::Uninitialized; 
        
        void updateSMA(const Candle& candle);
    };