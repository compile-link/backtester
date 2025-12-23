#pragma once

#include "Wallet.hpp"

class PositionManager{
    public:
        // explicit PositionManager(double initialBalance);
        explicit PositionManager(Wallet& wallet);
        
        bool openPosition(double price);
        bool closePosition(double price);

    private:
       Wallet& wallet_; 
};