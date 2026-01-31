#include "Menu.hpp"

#include <iostream>

Menu::Menu(const std::vector<std::string_view>& strategyNames, const std::vector<std::string>& dataFileNames) noexcept:
    strategyNames_(strategyNames), 
    dataFileNames_(std::move(dataFileNames)),
    config_{ 
        strategyNames_.empty() ? "" : strategyNames_.front(),
        dataFileNames_.empty() ? "" : dataFileNames_.front()
    } {}

void Menu::show(bool& startBacktest) {
    MenuState state = MenuState::Main;

    while(state != MenuState::Exit) {
        clear();
        printHeader();

        switch (state) {
            case MenuState::Main:
                state = showMainMenu(startBacktest);
                break;
            case MenuState::Settings:
                state = showSettings();
                break;
            case MenuState::StrategySettings:
                state = showStrategySettings();
                break;
            case MenuState::DataFileSettings:
                state = showDataFileSettings();
                break;
            default:
                state = MenuState::Exit;
        }
    }
}

MenuState Menu::showMainMenu(bool& startBacktest) {
    MenuState state = MenuState::Main;
    int option;

    std::cout << "1) Start Backtest\n";
    std::cout << "2) Settings\n";
    std::cout << "3) Exit\n";
    
    while (state == MenuState::Main) {
        std::cout << "Choose option: ";
        std::cin >> option;

        switch (option) {
            case 1:
                startBacktest = true;
                clear();
                state = MenuState::Exit;
                break;
            case 2:
                state = MenuState::Settings;
                break;
            case 3:
                startBacktest = false;
                state = MenuState::Exit;
                break;
            default:
                std::cout << "Invalid option, try again.\n";
        }
    }
    
    return state;
}

MenuState Menu::showSettings() {
    MenuState state = MenuState::Settings;
    int option;

    std::cout << "1) Strategy   [" << config_.strategyName << "]\n";
    std::cout << "2) Data file  [" << config_.dataFileName << "]\n";
    std::cout << "0) Back\n";

    while (state == MenuState::Settings) {
        std::cout << "Choose option: ";
        std::cin >> option;

        switch (option) {
            case 1:
                state = MenuState::StrategySettings;
                break;
            case 2:
                state = MenuState::DataFileSettings;
                break;
            case 0:
                state = MenuState::Main;
                break;
            default:
                std::cout << "Invalid option, try again.\n";
        }
    }
    
    return state;
}

MenuState Menu::showStrategySettings() {
    int option;

    for(std::size_t i=0; i< strategyNames_.size(); i++){
        std::cout << i+1 << ") " << strategyNames_[i] << "\n";
    }
    std::cout << "0) Back\n";
    
    while(true) {
        std::cout << "Choose option: ";
        std::cin >> option;
        if(option == 0) {
            return MenuState::Settings;
        }

        if(option >= 1 && option <= strategyNames_.size()) {
            config_.strategyName = strategyNames_[option-1];
        }
        else std::cout << "Invalid option, try again.\n";
    } 
}

MenuState Menu::showDataFileSettings() {
    int option;

    for(std::size_t i=0; i< dataFileNames_.size(); i++){
        std::cout << i+1 << ") " << dataFileNames_[i] << "\n";
    }
    std::cout << "0) Back\n";

    while(true) {
        std::cout << "Choose option: ";
        std::cin >> option;
        if(option == 0) {
            return MenuState::Settings;
        }

        if(option >= 1 && option <= dataFileNames_.size()) {
            config_.dataFileName = dataFileNames_[option-1];
        }
        else std::cout << "Invalid option, try again.\n";
    } 
} 

// Requires terminal to support ANSI escape codes
void Menu::clear() const noexcept {
    std::cout << "\033[2J\033[H";
}

void Menu::printHeader() const noexcept {
    std::cout << "\n";
    std::cout << "------------------------------\n";
    std::cout << "--------  Backtester  --------\n";
    std::cout << "------------------------------\n";
}