#include "Backtester.hpp"
#include <iostream>

void Backtester::run() {
    std::cout << "----------------------\n";
    std::cout << "Backtester started\n" << std::endl;

    showData();
    
    Signal signal;
    size_t index = 0;
    for(const auto& candle : dataManager.getCandles()){
        signal = strategy->onCandle(candle);
        
        switch(signal) { 
            case Signal::Buy:
                std::cout << "\n=====\nCandle index: " << index;
                std::cout << "\nBuy\n=====\n";
                break;
            case Signal::Sell:
                std::cout << "\n=====\nCandle index: " << index;
                std::cout << "\nSell\n======\n";
                break;
            case Signal::Wait:
                break;
        }

        ++index;
    }
    
    std::cout << "Final index: " << index << "\n";
    std::cout << "Done!\n";
    std::cout << "----------------------\n";
}

void Backtester::showData(){
    std::cout << "-----\n";
    std::cout << "Backtester data\n" << std::endl;

    const auto& candles = dataManager.getCandles();   
    std::cout << "Number of data points: " << candles.size() << "\n";
    std::cout << "Start date:            " << candles.front().date << "\n";
    std::cout << "End date:              " << candles.back().date << "\n";
    
    const auto candlesCount = 4;
    size_t count = 1;
    for (const auto& c : candles) {
       if(count >= candlesCount) break;

       std::cout << count++ << " " 
       << c.open << " " 
       << c.high << " " 
       << c.low << " " 
       << c.close << "\n"; 
    }
    
    std::cout << "Done!\n";
    std::cout << "-----\n";
}