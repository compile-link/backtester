#pragma once

#include "Strategy.hpp"

enum class MoveDirection {
    Bull,
    Bear
};

struct StrongMove {
    StrongMove(size_t minLen): minLength(minLen) {}

    const size_t minLength;
    std::vector<Candle> candles;
    MoveDirection direction;
    Candle pivotCandle;

    
    bool isComplete() const noexcept { return (candles.size() >= minLength); }
    bool isEngulfing(const Candle& candle) const noexcept;
    void update(const Candle& candle);
};

class StrategyEngulfing : public Strategy {
    public:
        StrategyEngulfing(size_t minLength = kMoveMinLength) noexcept: strongMove_(minLength) {}
        Signal onCandle(const Candle& candle) override; 
        
        // Strategy name enabling polymorphism
        std::string_view name() const noexcept override { return staticName(); } 

        // Strategy name can be called on class
        static std::string_view staticName() noexcept { return "Engulfing Candle"; } 
        
        // Strategy description enabling polymorphism
        void description() const noexcept override { return staticDescription(); };

        // Strategy description can be called on class
        static void staticDescription() noexcept;
        
    private:
        static const size_t kMoveMinLength = 2;
        StrongMove strongMove_;
};
