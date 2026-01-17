#pragma once

#include <string>

class Reporter {
    public:
        Reporter(): strategyName_("Strategy") {}
        void reportResults();

    private:
        std::string strategyName_;
        std::string dataFileName_;
        std::string startDate_; 
        std::string endDate_; 
        size_t candleCount_; 
        size_t tradeCount_;
        size_t winCount_;
        size_t lossCount_;
        double riskPerTrade_ = 0.0;
        double initialBalance_;
        double endBalance_;
        double pnL_;         
};