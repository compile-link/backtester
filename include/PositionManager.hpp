#pragma once
#include "Wallet.hpp"

class PositionManager{
    public:
        PositionManager(Wallet& w) : wallet(w) {};
        
        bool openPosition(double price);
        bool closePosition(double price);

    private:
       Wallet& wallet; 
};