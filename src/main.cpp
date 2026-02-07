#include "Backtester.hpp"
#include "Menu.hpp"
#include "Strategies/StrategyRegistry.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    try {
        std::string_view dataDir = (argc > 1) ? argv[1] : "";
        DataManager dataManager(dataDir);
        PositionManager positionManager{};
        Reporter reporter;

        BacktestContext ctx = {
            dataManager,
            positionManager,
            reporter
        };
        Backtester backtester(ctx);
        Menu menu(StrategyRegistry::strategyInfos(), dataManager.dataFileNames());

        bool startBacktest = false;
        do {
            menu.show(startBacktest);
            if(startBacktest){
                std::unique_ptr<Strategy> strategy = StrategyRegistry::createStrategy(menu.config().strategyInfo.name);
                backtester.setStrategy(std::move(strategy));
                dataManager.loadData(menu.config().dataFileName);
                backtester.run();
                reporter.summary();
                std::cout << "-- Press Enter to return to menu --\n";
                std::string dummy;
                std::getline(std::cin, dummy);
            }
        } while (startBacktest);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "Error occurred \n";
        return 1;
    }
}