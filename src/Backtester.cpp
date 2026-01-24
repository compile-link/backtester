#include "Backtester.hpp"
#include <iostream>

Backtester::Backtester(BacktestContext& ctx)
    : dataManager_(ctx.dataManager), positionManager_(ctx.positionManager), strategy_(ctx.strategy), reporter_(ctx.reporter) {}

void Backtester::run() {
    std::cout << "------------------------------\n";
    std::cout << "Backtesting... ";
    
    Signal signal;
    size_t index = 0;
    for(const auto& candle : dataManager_.getCandles()){
        signal = strategy_.onCandle(candle);
        
        switch(signal) { 
            case Signal::Buy:
                // std::cout << "\n=====\nCandle index: " << index << "\n";
                positionManager_.closeShort(candle.close);
                positionManager_.openLong(candle.close);
                break;
            case Signal::Sell:
                // std::cout << "\n=====\nCandle index: " << index << "\n";
                positionManager_.closeLong(candle.close); 
                positionManager_.openShort(candle.close);
                break;
            case Signal::Wait:
                break;
        }

        ++index;
    }

    reporter_.collectData(
        dataManager_.getSnapshot(),
        strategy_.getSnapshot(),
        positionManager_.getSnapshot(),
        positionManager_.getWalletSnapshot()
    );

    
    std::cout << "Done!\n";
}