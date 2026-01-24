#pragma once

#include "Candle.hpp"

#include <vector>
#include <functional>
#include <string_view>

struct DataManagerSnapshot {
    std::string fileName;
    std::string_view startDate; 
    std::string_view endDate; 
    size_t candleCount;
};

class DataManager {
    public:
        DataManager();
        bool loadData(const std::string& path);
        const std::vector<Candle>& getCandles() const noexcept { return candles_; }
        DataManagerSnapshot getSnapshot() const noexcept;
        
    private:
        static constexpr const char* kFilePath = "../data/eurusd_d.csv"; 
        std::vector<Candle> candles_; // data read from file, stored in memory

        std::string getFileName() const noexcept;
};