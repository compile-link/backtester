#pragma once

#include "Backtester.hpp"

enum class MenuState {
    Main,
    Settings,
    StrategySettings,
    DataFileSettings,
    Exit
};

struct Config {
    std::string_view strategyName;
    std::string_view dataFileName;
};

class Menu {
    public:
        Menu(Backtester& backtester, const std::vector<std::string_view>& strategyNames) noexcept;
        void show(bool& startBacktest);
        const Config& config() const noexcept { return config_; };
        
    private:
        Backtester& backtester_;
        const std::vector<std::string_view>& strategyNames_;
        Config config_;
        int dataFileIndex_ = 1;

        void startBacktest_();
        MenuState showMainMenu_(bool& startBacktest);
        MenuState showSettings_();
        MenuState showStrategySettings_(); 
        MenuState showDataFileSettings_(); 
        void clear_() const noexcept;
        void printHeader_() const noexcept;
};