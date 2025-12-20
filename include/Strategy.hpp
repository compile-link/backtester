#pragma once

#include "Candle.hpp"

enum class Signal {
    Buy,
    Sell,
    Wait
};

class Strategy {
    public:
        virtual Signal onCandle(const Candle& candle) = 0; 
        virtual ~Strategy() = default;
    };