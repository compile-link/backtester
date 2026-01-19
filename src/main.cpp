#include "Backtester.hpp"
#include <iostream>

int main() {
    Reporter reporter;
    auto onEventCallback = [&reporter](const auto& e){
        reporter.onEvent(e);
    };
    
    BacktestContext ctx = {
        DataManager{onEventCallback},
        PositionManager{onEventCallback},
        StrategySMA{onEventCallback}
    };
    Backtester backtester(ctx);
    backtester.run();
    reporter.summary();
    return 0;
}