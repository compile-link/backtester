#include "Reporter.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>

void Reporter::summary() {

    std::cout << "------------------------------\n";
    std::cout << "------ Backtest Results ------\n";
    std::cout << "------------------------------\n";
    std::cout << "Strategy: " << strategyName_ << "\n";
    std::cout << "Data File: " << dataFileName_ << "\n";
    std::cout << "Date Range: " << startDate_ << " - " << endDate_ << "\n";
    std::cout << "Candle Count: " << candleCount_ << "\n";
    std::cout << "Trade Count (W/L): " << tradeCount_ << " (" << winCount_ << "/" << lossCount_ << ")\n";

    if (tradeCount_ > 0){
        size_t winRate = static_cast<size_t>(std::round(static_cast<double>(winCount_) * 100.0 / tradeCount_));
        std::cout << "Win Rate: " << winRate << "%\n";
    }
    
    std::string riskPerTrade = "Unlimited";
    if (riskPerTrade_)
        riskPerTrade = std::to_string(*riskPerTrade_ * 100.0) + "%";
    else    
        riskPerTrade = "Unlimited";

    std::cout << "Risk per Trade: " << riskPerTrade << "\n";
    std::cout << "Initial Balance: " << std::fixed << std::setprecision(2) << initialBalance_ << "\n";
    std::cout << "End Balance: " << std::fixed << std::setprecision(2) << endBalance_ << "\n";
    std::cout << "PnL: " << std::fixed << std::setprecision(2) << pnL_ << "\n";
    std::cout << "------------------------------\n";
}

void Reporter::collectData(
    DataManagerSnapshot dataManagerSnapshot,
    StrategySnapshot strategySnapshot, 
    PositionManagerSnapshot positionManagerSnapshot, 
    WalletSnapshot walletSnapshot
) noexcept {
    // DataManager Data
    dataFileName_ = dataManagerSnapshot.fileName;
    startDate_ = dataManagerSnapshot.startDate; 
    endDate_ = dataManagerSnapshot.endDate; 
    candleCount_ = dataManagerSnapshot.candleCount; 

    // Strategy Data
    strategyName_ = strategySnapshot.strategyName;
    riskPerTrade_ = strategySnapshot.riskPerTrade;
    
    // PositionManager Data
    tradeCount_ = positionManagerSnapshot.tradeCount;
    winCount_ = positionManagerSnapshot.winCount;
    lossCount_ = positionManagerSnapshot.lossCount;

    // Wallet Data
    initialBalance_ = walletSnapshot.initialBalance;
    endBalance_ = walletSnapshot.endBalance;
    pnL_ = walletSnapshot.pnL;         
}