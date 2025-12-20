
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
        explicit StrategySMA(size_t p = DEFAULT_PERIOD);

        Signal onCandle(const Candle& candle) override; 
        

    private:
        static constexpr size_t DEFAULT_PERIOD = 14;
        size_t period_ = 0;
        std::vector<double> smaPoints_; 
        double sma_ = 0;
        CandleCloseSide prevCloseSide_ = CandleCloseSide::Uninitialized; 
        
        void updateSMA(const Candle& candle);
    };