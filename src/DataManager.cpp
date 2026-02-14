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
    auto name = dataFile->second.filename().string();
    if (dataFileName_ == name) {
        // Data file reused
        return false;
    }

    dataFileName_ = name;
    candles_.clear();
    
    std::ifstream file(path);
    if(!file.is_open()) {
        throw std::runtime_error("Can't open file");
    }

    std::string line;

    // skip header
    if (!std::getline(file, line) || line.empty()) {
        throw std::runtime_error("Missing header in " + fileName);
    }

    size_t lineNo = 1;
    while (std::getline(file, line)) {
        ++lineNo;
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string data;
        Candle candle{};

        auto parseDouble = [&](double& out) -> bool {
            try {
                if (!std::getline(ss, data, ',')) {
                    return false;
                }
                // remove trailing whitespace
                data.erase(data.find_last_not_of(" \t\n\r\f\v") + 1);
                size_t index = 0;
                out = std::stod(data, &index);
                return (index == data.size());
            } catch (...) {
                return false;
            }
        };

        if ((!std::getline(ss, candle.date, ',') || candle.date.empty()) ||
             !parseDouble(candle.open) ||
             !parseDouble(candle.high) ||
             !parseDouble(candle.low) ||
             !parseDouble(candle.close))
        {
            throw std::runtime_error("Data load failed " + fileName + ":" + std::to_string(lineNo));
        };

        candles_.push_back(std::move(candle));
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
        candles_.empty() ? std::string_view{"N/A"} : std::string_view{candles_.front().date},
        candles_.empty() ? std::string_view{"N/A"} : std::string_view{candles_.back().date},
        candles_.size()
    };
}
