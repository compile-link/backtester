#include "Backtester.hpp"
#include "DataManager.hpp"
#include "StrategySMA.hpp"
#include <iostream>

int main() {
    // auto strategySMA = std::make_unique<StrategySMA>();

    BacktestContext ctx = {
        DataManager{},
        PositionManager{},
        // std::move(strategySMA)
        StrategySMA{}
    };
    // Backtester backtester(std::move(ctx));
    Backtester backtester(ctx);
    backtester.run();
    std::cout << "Program finished successfully\n"; 
    return 0;
}