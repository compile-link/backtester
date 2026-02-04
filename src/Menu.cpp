#include "Menu.hpp"

#include <iostream>

Menu::Menu(const std::vector<StrategyInfo>& strategyInfos, const std::vector<std::string>& dataFileNames) noexcept:
    strategyInfos_(strategyInfos), 
    dataFileNames_(std::move(dataFileNames)),
    config_{ 
        {
            strategyInfos_.empty() ? "" : strategyInfos_.front().name,
            strategyInfos_.empty() ? std::function<void()>{} : strategyInfos_.front().description
        },
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
    std::cout << "3) Exit\n\n";
    
    while (state == MenuState::Main) {

        if(!chooseOption(option)) {
            continue;
        }

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

    std::cout << "1) Strategy   [" << config_.strategyInfo.name << "]\n";
    std::cout << "2) Data file  [" << config_.dataFileName << "]\n";
    std::cout << "0) Back\n\n";

    while (state == MenuState::Settings) {

        if(!chooseOption(option)) {
            continue;
        }

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

    printStrategySettingsOptions();

    while(true) {

        if(!chooseOption(option)) {
            continue;
        }
        
        if(option == 0) {
            return MenuState::Settings;
        }

        if(option >= 1 && option <= strategyInfos_.size()) {
            config_.strategyInfo = strategyInfos_[option-1];
            clear();
            printHeader();
            printStrategySettingsOptions();
        }
        else std::cout << "Invalid option, try again.\n";
    } 
}

void Menu::printStrategySettingsOptions() const {
    for(std::size_t i=0; i < strategyInfos_.size(); i++){
        std::cout << i+1 << ") " << strategyInfos_[i].name << "\n";
    }
    std::cout << "0) Back\n\n";
    
    std::cout << "Selected: " << config_.strategyInfo.name << "\n\n"; 
    config_.strategyInfo.description();
    std::cout << "\n";
}

MenuState Menu::showDataFileSettings() {
    int option;

    printDataFileSettingsOptions();

    while(true) {
        if(!chooseOption(option)) {
            continue;
        }

        if(option == 0) {
            return MenuState::Settings;
        }

        if(option >= 1 && option <= dataFileNames_.size()) {
            config_.dataFileName = dataFileNames_[option-1];
            clear();
            printHeader();
            printDataFileSettingsOptions();
        }
        else std::cout << "Invalid option, try again.\n";
    } 
} 

void Menu::printDataFileSettingsOptions() const {
    for(std::size_t i=0; i< dataFileNames_.size(); i++){
        std::cout << i+1 << ") " << dataFileNames_[i] << "\n";
    }
    std::cout << "0) Back\n\n";

    std::cout << "Selected: " << config_.dataFileName << "\n\n";
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

bool Menu::chooseOption(int& option) const {
    std::cout << "Choose option: ";
    
    if(!(std::cin >> option)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input, try again.\n";
        return false;
    }
    
    // Disregard the rest of the line to avoid leftover characters affecting the next read
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
}
