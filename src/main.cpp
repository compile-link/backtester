#include "Backtester.hpp"
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
    backtester.run();
    reporter.summary();
    return 0;
}