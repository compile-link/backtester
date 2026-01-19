#pragma once

#include <cstddef>
#include <string_view>
#include <variant>

struct StrategyEvent {
    std::string_view strategyName;
};

struct TradeEvent {
        size_t tradeCount;
        size_t winCount;
        size_t lossCount;
        double riskPerTrade;
};

struct WalletEvent {
        double initialBalance;
        double endBalance;
        double pnL;         
};

using Event = std::variant<StrategyEvent, TradeEvent, WalletEvent>; 