#include "Backtester.hpp"
#include <iostream>

Backtester::Backtester(BacktestContext& ctx)
    : dataManager_(ctx.dataManager), positionManager_(ctx.positionManager), reporter_(ctx.reporter) {}

void Backtester::run() {
    Signal signal;
    std::optional<double> stopLoss;
    for(const auto& candle : dataManager_.getCandles()){
        stopLoss = std::nullopt;
        signal = strategy_->onCandle(candle, stopLoss);
        positionManager_.onCandle(candle, signal, stopLoss);
    }

    reporter_.collectData(
        dataManager_.getSnapshot(),
        strategy_->getSnapshot(),
        positionManager_.getSnapshot(),
        positionManager_.getWalletSnapshot()
    );
    
    positionManager_.reset();
}