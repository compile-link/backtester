#pragma once

#include "DataManager.hpp"
#include "Strategy.hpp"
#include "PositionManager.hpp"

#include <string>

class Reporter {
    public:
        void summary();
        void collectData(
            DataManagerSnapshot dataManagerSnapshot,
            StrategySnapshot strategySnapshot, 
            PositionManagerSnapshot positionManagerSnapshot, 
            WalletSnapshot walletSnapshot
        ) noexcept;

        // void onEvent(const Event& e);

    private:
        std::string_view dataFileName_;
        std::string_view startDate_; 
        std::string_view endDate_; 
        size_t candleCount_; 

        std::string_view strategyName_;
        std::optional<double> riskPerTrade_;

        size_t tradeCount_;
        size_t winCount_;
        size_t lossCount_;

        double initialBalance_;
        double endBalance_;
        double pnL_;         
};