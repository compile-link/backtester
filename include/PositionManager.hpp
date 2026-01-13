#pragma once

#include "Wallet.hpp"

enum class PositionType {
    Long,
    Short
};

struct Position {
    double openPrice;
    double closePrice;
    double sizeFactor;
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

class PositionManager{
    public:
        explicit PositionManager();
        
        bool openLong(double price, double sizeFactor=1.0);
        bool openShort(double price, double sizeFactor=1.0);
        bool closeLong(double price);
        bool closeShort(double price);

    private:
        Position longPosition_; 
        Position shortPosition_; 
        Wallet wallet_;

        bool openPosition(Position& position, double price, double sizeFactor);
        bool closePosition(Position& position, double price);

};