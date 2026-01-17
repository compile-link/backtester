#include "Reporter.hpp"
#include <iostream>

void Reporter::reportResults() {

    std::cout << "------ Backtest Results ------\n";
    std::cout << "Strategy: " << strategyName_ << "\n";
    std::cout << "Data File: " << dataFileName_ << "\n";
    std::cout << "Date Range: " << startDate_ << " - " << endDate_ << "\n";
    std::cout << "Candle Count: " << candleCount_ << "\n";
    std::cout << "Trade Count (W/L): " << tradeCount_ << " (" << winCount_ << "/" << lossCount_ << ")\n";

    if (tradeCount_ > 0){
        double winRate = winCount_ / tradeCount_ * 100.0;
        std::cout << "Win Rate: " << winRate << "%\n";
    }
    
    std::string riskPerTrade = "Unlimited";
    if (riskPerTrade_ > 0.0)
        riskPerTrade = std::to_string(riskPerTrade_ * 100.0) + "%";
    else    
        riskPerTrade = "Unlimited";

    std::cout << "Risk per Trade: " << riskPerTrade << "\n";
    std::cout << "Initial Balance: " << initialBalance_ << "\n";
    std::cout << "End Balance: " << endBalance_ << "\n";
    std::cout << "PnL: " << pnL_ << "\n";
    std::cout << "------------------------------\n";
}