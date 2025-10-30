#pragma once
#include "DataManager.hpp"
#include "Strategy.hpp"
#include "Wallet.hpp"

class Backtester {
    public:
        Backtester(DataManager& d): dataManager(d){};
        void run();         
    private:
        //std::unique_ptr<Data> data;
        DataManager& dataManager;
        Strategy strategy;
        Wallet wallet;
};