#pragma once

#include "DataManager.hpp"
#include "Strategy.hpp"
#include "Wallet.hpp"

#include <memory>

class Backtester {
    public:
        Backtester(DataManager& dm, std::unique_ptr<Strategy> s)
            : dataManager(dm), strategy(std::move(s)){};
        void run();         
    private:
        DataManager& dataManager;
        std::unique_ptr<Strategy> strategy;
        Wallet wallet;
        
        void showData();
};