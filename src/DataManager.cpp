#include "DataManager.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

DataManager::DataManager() {
    loadData(kFilePath);
}

bool DataManager::loadData(const std::string& path){

    std::cout << "------------------------------\n";
    std::cout << "Reading csv file " << path << "... ";
    
    std::ifstream file(path);
    if(!file.is_open()) {
        std::cerr << "Error: can't open file " << path << "\n";
        return false;
    }

    std::string line;

    std::getline(file, line); // skip header
    // std::cout << line << "\n";
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string data;
        Candle candle;

        std::getline(ss, candle.date, ','); 

        std::getline(ss, data, ','); 
        candle.open = std::stod(data);

        std::getline(ss, data, ','); 
        candle.high = std::stod(data);

        std::getline(ss, data, ','); 
        candle.low = std::stod(data);

        std::getline(ss, data, ','); 
        candle.close = std::stod(data);

        candles_.push_back(candle);
    }

    file.close();
    
    std::cout << "Done!\n";

    return !candles_.empty();
}

DataManagerSnapshot DataManager::getSnapshot() const noexcept {
    return {
        getFileName(),
        candles_.front().date, 
        candles_.back().date,
        candles_.size()
    };
}

std::string DataManager::getFileName() const noexcept {
std::filesystem::path p(kFilePath);
std::string s = p.stem().string();
    return std::filesystem::path(kFilePath).stem().string();
};
