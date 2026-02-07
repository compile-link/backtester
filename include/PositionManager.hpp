#pragma once

#include "Wallet.hpp"
#include "Candle.hpp"
#include "Strategies/Strategy.hpp"

#include <functional>
#include <optional>

enum class PositionType {
    Long,
    Short,
    Undefined
};

struct Position {
    double openPrice;
    double closePrice;
    std::optional<double> stopLoss;
    std::optional<double> profitTarget;
    double sizeFactor; // Implies position size, eg. 1.0 uses full balance to open a position
    PositionType type = PositionType::Undefined;
    bool isOpen = false;
    
    double priceChangePercentage() const {
        if(isOpen) return 0.0;

        double change = (closePrice - openPrice)/openPrice;
        
        // flip sign if short
        if(type == PositionType::Short) 
            change*=-1.0;
        
        return change;
    }

};

struct PositionManagerSnapshot {
    size_t tradeCount;
    size_t winCount;
    size_t lossCount;
    std::optional<double> riskPerTrade;
};

class PositionManager{
    public:
        bool openLong(const double price, const std::optional<double> stopLoss = std::nullopt, const double sizeFactor = 1.0);
        bool openShort(const double price, const std::optional<double> stopLoss = std::nullopt, const double sizeFactor = 1.0);
        bool closeLong(const double price);
        bool closeShort(const double price);
        void onCandle(const Candle& candle, const Signal& signal, const std::optional<double> stopLoss);
        void setRisk(std::optional<double> rr) noexcept { 
            riskReward_ = rr; 
            if (!riskReward_) {
                riskPerTrade_ = std::nullopt; 
            }
        }
        
        PositionManagerSnapshot getSnapshot() const noexcept;
        WalletSnapshot getWalletSnapshot() const noexcept; 

    private:
        static constexpr double kDefaultRiskPerTrade = 1.0; // Percentage    

        Position position_; 
        
        Wallet wallet_;
        std::optional<double> riskReward_ = std::nullopt;
        
        size_t tradeCount_ = 0;
        size_t winCount_ = 0;
        size_t lossCount_ = 0;
        std::optional<double> riskPerTrade_ = kDefaultRiskPerTrade;

        bool openPosition(const PositionType type, const double price, const std::optional<double> stopLoss = std::nullopt, const double sizeFactor = 1.0);
        bool closePosition(const double price);
        bool isRiskUnlimited() const noexcept { return (!position_.stopLoss.has_value() || !position_.profitTarget.has_value()); }
        
};