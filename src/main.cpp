#include "Backtester.hpp"
#include "Menu.hpp"
#include "Strategies/StrategyRegistry.hpp"

#include <iostream>

int main() {
    Reporter reporter;
    BacktestContext ctx = {
        DataManager{},
        PositionManager{},
        reporter
    };
    Backtester backtester(ctx);
    Menu menu(backtester, StrategyRegistry::StrategyNames());
    
    bool startBacktest = false;
    menu.show(startBacktest);
    if(startBacktest){ 
        std::unique_ptr<Strategy> strategy = StrategyRegistry::CreateStrategy(menu.config().strategyName);
        backtester.setStrategy(std::move(strategy));
        backtester.run();
        reporter.summary();
    }

    return 0;
}