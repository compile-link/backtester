#pragma once

#include "DataManager.hpp"
#include "Strategy.hpp"
#include "StrategySMA.hpp"
#include "PositionManager.hpp"
#include "Reporter.hpp"
#include "Events.hpp"

#include <memory>

struct BacktestContext {
    DataManager dataManager;
    PositionManager positionManager;
    StrategySMA strategy;
};

class Backtester {
    public:
        explicit Backtester(BacktestContext& ctx);
        void run();         
    private:
        DataManager& dataManager_;
        PositionManager& positionManager_;
        Strategy& strategy_;
        
        void showData_();
};