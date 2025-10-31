#pragma once
#include "DataManager.hpp"
#include "Strategy.hpp"
#include "Wallet.hpp"

class Backtester {
    public:
        Backtester(DataManager& dm): dataManager(dm){};
        void run();         
    private:
        DataManager& dataManager;
        Strategy strategy;
        Wallet wallet;
};