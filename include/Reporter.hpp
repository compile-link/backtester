#pragma once

#include "Events.hpp"

#include <string>

class Reporter {
    public:
        Reporter(): strategyName_("Strategy") {}
        void summary();
        void onEvent(const Event& e);

    private:
        std::string_view strategyName_;
        std::string_view dataFileName_;
        std::string_view startDate_; 
        std::string_view endDate_; 
        size_t candleCount_; 
        size_t tradeCount_;
        size_t winCount_;
        size_t lossCount_;
        double riskPerTrade_ = 0.0;
        double initialBalance_;
        double endBalance_;
        double pnL_;         
};