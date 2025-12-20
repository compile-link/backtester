#include "Backtester.hpp"
#include "DataManager.hpp"
#include "StrategySMA.hpp"
#include <iostream>

int main() {
    DataManager dataManager;
    auto strategySMA = std::make_unique<StrategySMA>();
    Backtester backtester(dataManager, std::move(strategySMA));
    backtester.run();
    std::cout << "Program finished successfully\n"; 
    return 0;
}