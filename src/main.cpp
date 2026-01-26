#include "Backtester.hpp"
#include "Menu.hpp"

#include <iostream>

int main() {
    Reporter reporter;
    BacktestContext ctx = {
        DataManager{},
        PositionManager{},
        StrategySMA{},
        reporter
    };
    Backtester backtester(ctx);
    Menu menu(backtester);
    
    bool startBacktest = false;
    menu.show(startBacktest);
    if(startBacktest){ 
        backtester.run();
        reporter.summary();
    }

    return 0;
}