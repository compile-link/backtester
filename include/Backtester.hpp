#pragma once

#include "DataManager.hpp"
#include "Strategies/Strategy.hpp"
#include "Strategies/StrategySMA.hpp"
#include "PositionManager.hpp"
#include "Reporter.hpp"

#include <memory>

struct BacktestContext {
    DataManager& dataManager;
    PositionManager& positionManager;
    Reporter& reporter;
};

class Backtester {
    public:
        explicit Backtester(BacktestContext& ctx);
        void run();         
        void setStrategy(std::unique_ptr<Strategy> strategy) { 
            strategy_ = std::move(strategy); 
            positionManager_.setRisk(strategy_ ? strategy_->getRiskReward() : std::nullopt);
        }

    private:
        DataManager& dataManager_;
        PositionManager& positionManager_;
        Reporter& reporter_;
        std::unique_ptr<Strategy> strategy_;
};