
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
        Signal onCandle(const Candle& candle, std::optional<double>& stopLoss) override; 

        // Strategy name enabling polymorphism
        std::string_view name() const noexcept override { return staticName(); } 
        
        // Strategy name can be called on class
        static std::string_view staticName() noexcept { return "Simple Moving Average (SMA)"; } 

        // Strategy description enabling polymorphism
        void description() const noexcept override { return staticDescription(); };

        // Strategy description can be called on class
        static void staticDescription() noexcept;

    private:
        static constexpr size_t kDefaultPeriod = 14;
        std::vector<double> smaPoints_; 
        double sma_ = 0.0;
        CandleCloseSide prevCloseSide_ = CandleCloseSide::Uninitialized; 
        
        void updateSMA(const Candle& candle);
    };