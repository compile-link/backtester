#pragma once

#include "Backtester.hpp"
#include "Strategies/StrategyInfo.hpp"

#include <iostream>

enum class MenuState {
    Main,
    Settings,
    StrategySettings,
    DataFileSettings,
    Exit
};

struct Config {
    StrategyInfo strategyInfo;
    std::string dataFileName;
};

class Menu {
    public:
        Menu(const std::vector<StrategyInfo>& strategyInfos, const std::vector<std::string>& dataFileNames) noexcept;
        void show(bool& startBacktest);
        const Config& config() const noexcept { return config_; };
        
    private:
        const std::vector<StrategyInfo> strategyInfos_;
        const std::vector<std::string> dataFileNames_;
        Config config_;

        MenuState showMainMenu(bool& startBacktest);
        MenuState showSettings();
        MenuState showStrategySettings(); 
        void printStrategySettingsOptions() const;
        MenuState showDataFileSettings(); 
        void printDataFileSettingsOptions() const; 
        void clear() const noexcept;
        void printHeader() const noexcept;
        
        bool chooseOption(int& option) const;
};