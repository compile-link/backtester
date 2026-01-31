#pragma once

#include "Wallet.hpp"

#include <functional>

enum class PositionType {
    Long,
    Short
};

struct Position {
    double openPrice;
    double closePrice;
    double sizeFactor; // Implies position size, eg. 1.0 uses full balance to open a position
    PositionType type;
    bool isOpen = false;
    
    double priceChangePercentage() const {
        if(isOpen) return 0.0;

        double change = (closePrice - openPrice)/openPrice;
        
        // flip sign if short
        if(type == PositionType::Short) 
            change*=-1.0;
        
        return change;
    }

};

struct PositionManagerSnapshot {
    size_t tradeCount;
    size_t winCount;
    size_t lossCount;
};

class PositionManager{
    public:
        PositionManager();
        
        bool openLong(double price, double sizeFactor=1.0);
        bool openShort(double price, double sizeFactor=1.0);
        bool closeLong(double price);
        bool closeShort(double price);
        
        PositionManagerSnapshot getSnapshot() const noexcept;
        WalletSnapshot getWalletSnapshot() const noexcept; 

    private:
        Position longPosition_; 
        Position shortPosition_; 
        Wallet wallet_;
        
        size_t tradeCount_ = 0;
        size_t winCount_ = 0;
        size_t lossCount_ = 0;

        bool openPosition(Position& position, double price, double sizeFactor);
        bool closePosition(Position& position, double price);
        
};