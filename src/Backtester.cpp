#include "Backtester.hpp"
#include <iostream>

void Backtester::run() {
    std::cout << "Backtester started\n" << std::endl;

    const auto& candles = dataManager.getData();   
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
    
    strategy->signal();
    
    std::cout << "Bactester finished\n";
}
