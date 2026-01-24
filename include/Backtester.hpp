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
    StrategySMA strategy;
    Reporter& reporter;
};

class Backtester {
    public:
        explicit Backtester(BacktestContext& ctx);
        void run();         
    private:
        DataManager& dataManager_;
        PositionManager& positionManager_;
        Strategy& strategy_;
        Reporter& reporter_;
        
        void showData_();
};