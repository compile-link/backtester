#pragma once

#include "DataManager.hpp"
#include "Strategies/Strategy.hpp"
#include "PositionManager.hpp"

#include <string>
#include <optional>

class Reporter {
    public:
        void summary();
        void collectData(
            DataManagerSnapshot dataManagerSnapshot,
            StrategySnapshot strategySnapshot, 
            PositionManagerSnapshot positionManagerSnapshot, 
            WalletSnapshot walletSnapshot
        ) noexcept;

    private:
        std::string_view dataFileName_;
        std::string_view startDate_; 
        std::string_view endDate_; 
        size_t candleCount_; 

        std::string_view strategyName_;
        std::optional<double> riskReward_;

        size_t tradeCount_;
        size_t winCount_;
        size_t lossCount_;
        std::optional<double> riskPerTrade_;

        double initialBalance_;
        double endBalance_;
        double pnL_;         
};