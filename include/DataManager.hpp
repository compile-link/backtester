#pragma once

#include "Candle.hpp"
#include <vector>

class DataManager {
    public:
        DataManager(){
            loadData(kFilePath);
        }
        bool loadData(const std::string& path);
        const std::vector<Candle>& getCandles() const { return candles_; }
        
    private:
        static constexpr const char* kFilePath = "../data/eurusd_d.csv"; 
        std::vector<Candle> candles_; // data read from file, stored in memory
};