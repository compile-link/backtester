#pragma once

#include "DataManager.hpp"
#include "Strategy.hpp"
#include "Wallet.hpp"

#include <memory>

class Backtester {
    public:
        explicit Backtester(DataManager& dataManager, std::unique_ptr<Strategy> strategy);
        void run();         
    private:
        DataManager& dataManager_;
        std::unique_ptr<Strategy> strategy_;
        
        void showData();
};