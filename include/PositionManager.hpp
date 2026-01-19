#pragma once

#include "Wallet.hpp"
#include "Events.hpp"

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

class PositionManager{
    public:
        explicit PositionManager(std::function<void (const Event&)> callback);
        
        bool openLong(double price, double sizeFactor=1.0);
        bool openShort(double price, double sizeFactor=1.0);
        bool closeLong(double price);
        bool closeShort(double price);

    private:
        Position longPosition_; 
        Position shortPosition_; 
        Wallet wallet_;

        bool openPosition_(Position& position, double price, double sizeFactor);
        bool closePosition_(Position& position, double price);
        
        std::function<void (const Event&)> notify_; 
};