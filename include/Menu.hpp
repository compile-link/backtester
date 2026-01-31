#pragma once

#include "Backtester.hpp"

#include <iostream>

enum class MenuState {
    Main,
    Settings,
    StrategySettings,
    DataFileSettings,
    Exit
};

struct Config {
    std::string_view strategyName;
    std::string dataFileName;
};

class Menu {
    public:
        Menu(const std::vector<std::string_view>& strategyNames, const std::vector<std::string>& dataFileNames) noexcept;
        void show(bool& startBacktest);
        const Config& config() const noexcept { return config_; };
        
    private:
        const std::vector<std::string_view> strategyNames_;
        const std::vector<std::string> dataFileNames_;
        Config config_;

        MenuState showMainMenu(bool& startBacktest);
        MenuState showSettings();
        MenuState showStrategySettings(); 
        MenuState showDataFileSettings(); 
        void clear() const noexcept;
        void printHeader() const noexcept;
};