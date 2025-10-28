#pragma once
#include <vector>
#include <string>

struct OHLC {
    double open;
    double high;
    double low;
    double close;
};

class Data {
    public:
        Data(){
            // std::cout << "read csv should be here\n";
            readCSV("file.txt");
        }
        bool readCSV(const std::string& filename);
        
    private:
        std::vector<OHLC> data; // data read from file, stored in memory
};