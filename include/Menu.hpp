#pragma once

#include "Backtester.hpp"

enum class MenuState {
    Main,
    Settings,
    StrategySettings,
    DataFileSettings,
    Exit
};

class Menu {
    public:
        explicit Menu(Backtester& backtester) noexcept: backtester_(backtester) {}
        void show(bool& startBacktest);
        
    private:
        Backtester& backtester_;
        int strategyIndex_ = 1;
        int dataFileIndex_ = 1;

        void startBacktest_();
        MenuState showMainMenu_(bool& startBacktest);
        MenuState showSettings_();
        MenuState showStrategySettings_(); 
        MenuState showDataFileSettings_(); 
        void clear_() const noexcept;
        void printHeader_() const noexcept;
};