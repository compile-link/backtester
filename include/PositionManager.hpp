#pragma once

#include "Wallet.hpp"

class PositionManager{
    public:
        explicit PositionManager();
        
        bool openPosition(double price);
        bool closePosition(double price);

    private:
       Wallet wallet_;
};