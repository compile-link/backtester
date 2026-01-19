#include "Reporter.hpp"
#include <iostream>

void Reporter::summary() {

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

void Reporter::onEvent(const Event& e) {
    std::visit([this](auto&& ev) {
        using T = std::decay_t<decltype(ev)>;
        if constexpr (std::is_same_v<T, StrategyEvent>) {
            strategyName_ = ev.strategyName;
        } else if constexpr (std::is_same_v<T, TradeEvent>) {
            tradeCount_ = ev.tradeCount;
            winCount_ = ev.winCount;
            lossCount_ = ev.lossCount;
            riskPerTrade_ = ev.riskPerTrade;
        } else if constexpr (std::is_same_v<T, WalletEvent>) {
            initialBalance_ = ev.initialBalance;
            endBalance_ = ev.endBalance;
            pnL_ = ev.pnL;         
        }
    }, e);    
}