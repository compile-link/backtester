#pragma once

#include "Candle.hpp"

#include <vector>
#include <functional>
#include <string_view>
#include <filesystem>
#include <map>

struct DataManagerSnapshot {
    std::string_view fileName;
    std::string_view startDate; 
    std::string_view endDate; 
    size_t candleCount;
};

class DataManager {
    public:
        explicit DataManager(std::string_view dataDir = "");
        bool loadData(const std::string fileName);
        std::vector<std::string> dataFileNames() const;
        const std::vector<Candle>& getCandles() const noexcept { return candles_; }
        DataManagerSnapshot getSnapshot() const noexcept;
        
    private:
        std::string_view dataDir_; 
        std::string dataFileName_;
        std::map<std::string, std::filesystem::path> dataFilesMap_;
        std::vector<Candle> candles_; // data read from file, stored in memory

        void scanDataDirectory();
};