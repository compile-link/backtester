
#pragma once

#include "Strategy.hpp"


class StrategyMA: public Strategy {
    public:
        double signal() override; 
    };