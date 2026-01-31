
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
        explicit StrategySMA(size_t p = kDefaultPeriod) noexcept;
        Signal onCandle(const Candle& candle) override; 

        // Strategy name on class
        static std::string_view Name() noexcept { return "Simple Moving Average (SMA)"; } 
        //
        // Strategy name enabling polymorphism
        std::string_view name() const noexcept override { return Name(); } 

    private:
        static constexpr size_t kDefaultPeriod = 14;
        size_t period_ = 0;
        std::vector<double> smaPoints_; 
        double sma_ = 0;
        CandleCloseSide prevCloseSide_ = CandleCloseSide::Uninitialized; 
        
        void updateSMA(const Candle& candle);
    };