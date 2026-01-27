#include "Menu.hpp"

#include <iostream>

Menu::Menu(Backtester& backtester, const std::vector<std::string_view>& strategyNames) noexcept:
    backtester_(backtester), 
    strategyNames_(strategyNames), 
    config_{ strategyNames.empty() ? "" : strategyNames.front() } {}

void Menu::show(bool& startBacktest) {
    MenuState state = MenuState::Main;

    while(state != MenuState::Exit) {
        clear_();
        printHeader_();

        switch (state) {
            case MenuState::Main:
                state = showMainMenu_(startBacktest);
                break;
            case MenuState::Settings:
                state = showSettings_();
                break;
            case MenuState::StrategySettings:
                state = showStrategySettings_();
                break;
            case MenuState::DataFileSettings:
                state = showDataFileSettings_();
                break;
            default:
                state = MenuState::Exit;
        }
    }
    
    if(startBacktest) {
        clear_();
        startBacktest_(); 
    }
}

void Menu::startBacktest_() {}

MenuState Menu::showMainMenu_(bool& startBacktest) {
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

MenuState Menu::showSettings_() {
    MenuState state = MenuState::Settings;
    int option;

    std::cout << "1) Strategy   [" << config_.strategyName << "]\n";
    std::cout << "2) Data file\n";
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

MenuState Menu::showStrategySettings_() {
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

MenuState Menu::showDataFileSettings_() {
    int option;

    std::cout << "1) eurusd\n";
    std::cout << "2) gold\n";
    std::cout << "3) nq\n";
    std::cout << "0) Back\n";

    while(true) {
        std::cout << "Choose option: ";
        std::cin >> option;
        if(option == 0) {
            return MenuState::Settings;
        }

        if(option >= 1 && option <= 3) {
            dataFileIndex_ = option;
        }
        else std::cout << "Invalid option, try again.\n";
    } 
} 

// Requires terminal to support ANSI escape codes
void Menu::clear_() const noexcept {
    std::cout << "\033[2J\033[H";
}

void Menu::printHeader_() const noexcept {
    std::cout << "\n";
    std::cout << "------------------------------\n";
    std::cout << "--------  Backtester  --------\n";
    std::cout << "------------------------------\n";
}