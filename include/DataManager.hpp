#pragma once
#include <vector>
#include <string>

struct OHLC {
    double open;
    double high;
    double low;
    double close;
};

class DataManager {
    public:
        DataManager(){
            // std::cout << "read csv should be here\n";
            readCSV("file.txt");
        }
        bool readCSV(const std::string& path);
        std::vector<OHLC> getData() { return candles_; }
        
    private:
        std::vector<OHLC> candles_; // data read from file, stored in memory
};