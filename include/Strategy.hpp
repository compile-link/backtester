#pragma once

#include "Candle.hpp"
#include "Events.hpp"

#include <functional>

enum class Signal {
    Buy,
    Sell,
    Wait
};

class Strategy {
    public:
        explicit Strategy (std::function<void (const Event&)> callback): notify_(callback) {}

        virtual Signal onCandle(const Candle& candle) = 0; 
        virtual ~Strategy() = default;
        
    protected:
        std::function<void (const Event&)> notify_; 
    };