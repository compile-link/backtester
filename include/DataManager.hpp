#pragma once

#include "Candle.hpp"
#include "Events.hpp"

#include <vector>
#include <functional>

class DataManager {
    public:
        explicit DataManager(std::function<void (const Event&)> callback);
        bool loadData(const std::string& path);
        const std::vector<Candle>& getCandles() const { return candles_; }
        
    private:
        static constexpr const char* kFilePath = "../data/eurusd_d.csv"; 
        std::vector<Candle> candles_; // data read from file, stored in memory
        std::function<void (const Event&)> notify_;
};