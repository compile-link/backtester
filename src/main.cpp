#include "Backtester.hpp"
#include "DataManager.hpp"
#include "StrategyMA.hpp"
#include <iostream>

int main() {
    DataManager dataManager;
    auto strategyMA = std::make_unique<StrategyMA>();
    Backtester backtester(dataManager, std::move(strategyMA));
    backtester.run();
    std::cout << "Program finished successfully\n"; 
    return 0;
}