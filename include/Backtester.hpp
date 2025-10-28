#pragma once
#include "Data.hpp"
#include "Strategy.hpp"
#include "Wallet.hpp"

class Backtester {
    public:
        Backtester(Data& d): data(d){};
        void run();         
    private:
        //std::unique_ptr<Data> data;
        Data& data;
        Strategy strategy;
        Wallet wallet;
};