#pragma once
#include <vector>
#include <string>

struct Candle {
    std::string date;
    double open;
    double high;
    double low;
    double close;
};

class DataManager {
    public:
        DataManager(){
            loadData(kFilePath_);
        }
        bool loadData(const std::string& path);
        std::vector<Candle> getData() { return candles_; }
        
    private:
        static constexpr const char* kFilePath_ = "../data/eurusd_d.csv"; 
        std::vector<Candle> candles_; // data read from file, stored in memory
};