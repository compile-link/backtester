#include "Backtester.hpp"
#include "Data.hpp"
#include <iostream>

int main() {
    Data data;
    Backtester backtester(data);
    backtester.run();
    std::cout << "Program finished successfully\n"; 
    return 0;
}