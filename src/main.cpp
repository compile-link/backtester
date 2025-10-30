#include "Backtester.hpp"
#include "DataManager.hpp"
#include <iostream>

int main() {
    DataManager dataManager;
    Backtester backtester(dataManager);
    backtester.run();
    std::cout << "Program finished successfully\n"; 
    return 0;
}