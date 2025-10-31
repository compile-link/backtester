#include "DataManager.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

bool DataManager::readCSV(const std::string& path){
    std::cout << "Reading csv file... ";
    
    std::ifstream file(path);
    if(!file.is_open()) {
        std::cerr << "Error: can't open file " << path << "\n";
        return false;
    }
    
    std::string line;

    std::getline(file, line); // skip header
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