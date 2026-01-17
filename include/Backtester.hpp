#pragma once

#include "DataManager.hpp"
#include "Strategy.hpp"
#include "StrategySMA.hpp"
#include "PositionManager.hpp"
#include "Reporter.hpp"

#include <memory>

struct BacktestContext {
    DataManager dataManager;
    PositionManager positionManager;
    // std::unique_ptr<Strategy> strategy;
    StrategySMA strategy;
    Reporter reporter;
};


class Backtester {
    public:
        explicit Backtester(BacktestContext& ctx);
        void run();         
    private:
        DataManager& dataManager_;
        PositionManager& positionManager_;
        // std::unique_ptr<Strategy> strategy_;
        Strategy& strategy_;
        Reporter& reporter_;
        
        void showData();
};