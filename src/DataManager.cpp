#include "DataManager.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

DataManager::DataManager(std::string_view dataDir): dataDir_(dataDir) {
   if (!std::filesystem::exists(dataDir_)) {
       if (std::filesystem::exists("./data")) {
            dataDir_ = "./data";
        } else if (std::filesystem::exists("../data")) {
            dataDir_ = "../data";
        }
    }

    scanDataDirectory();
}

void DataManager::scanDataDirectory() {
    if (!std::filesystem::exists(dataDir_)) {
        throw std::runtime_error("Data folder not found!");
    }

    std::vector<std::filesystem::path> files;
    
    dataFilesMap_.clear();
    for (const auto& entry: std::filesystem::directory_iterator(dataDir_)) {
        if(entry.is_regular_file()) {
            auto fileName = entry.path().stem().string();
            dataFilesMap_.emplace(fileName, entry.path());
        }
    }
}

bool DataManager::loadData(const std::string fileName) {

    auto dataFile = dataFilesMap_.find(fileName);
    if (dataFile == dataFilesMap_.end()) {
        throw std::out_of_range("Data file not initialized: " + fileName);
    }
    auto path = dataFile->second.string();
    dataFileName_ = dataFile->second.filename().string();
    
    // std::cout << "------------------------------\n";
    // std::cout << "Reading file " << dataFileName_ << "...   ";
    
    std::ifstream file(path);
    if(!file.is_open()) {
        throw std::runtime_error("Can't open file");
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

    return !candles_.empty();
}

std::vector<std::string> DataManager::dataFileNames() const {
    std::vector<std::string> dataFileNames;   
    dataFileNames.reserve(dataFilesMap_.size());
    for (const auto& [dataFileName, _]: dataFilesMap_) {
        dataFileNames.push_back(dataFileName);
    }
    
    return dataFileNames;
}

DataManagerSnapshot DataManager::getSnapshot() const noexcept {
    return {
        dataFileName_,
        candles_.front().date, 
        candles_.back().date,
        candles_.size()
    };
}
