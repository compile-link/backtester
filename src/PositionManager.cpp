#include "PositionManager.hpp"
#include <iostream>

bool PositionManager::openLong(const double price, const std::optional<double> stopLoss, const double sizeFactor){
    return openPosition(PositionType::Long, price, stopLoss, sizeFactor);
}

bool PositionManager::openShort(const double price, const std::optional<double> stopLoss, const double sizeFactor){
    return openPosition(PositionType::Short, price, stopLoss, sizeFactor);
}

bool PositionManager::closeLong(const double price){
    return closePosition(price);
}

bool PositionManager::closeShort(const double price){
    return closePosition(price);
}

void PositionManager::onCandle(const Candle& candle, const Signal& signal, const std::optional<double> stopLoss) {
    if (isRiskUnlimited()) {
        if (position_.isOpen && (signal == Signal::Buy || signal == Signal::Sell)) {
            closePosition(candle.close);
        } 
    }

    if (!position_.isOpen) {
        switch(signal) { 
            case Signal::Buy:
                openLong(candle.close, stopLoss);
                break;
            case Signal::Sell:
                openShort(candle.close, stopLoss);
                break;
            case Signal::Wait:
                break;
        }
    } else if (!isRiskUnlimited()) {
        bool slHit = false;
        bool tpHit = false;
        slHit = (*position_.stopLoss >= candle.low && *position_.stopLoss <= candle.high);
        tpHit = (*position_.profitTarget >= candle.low && *position_.profitTarget <= candle.high);
        // In case last candle contains both SL and TP we approximate the value closer to candle open was hit first
        if (slHit && tpHit) {
            if (std::abs(*position_.stopLoss - candle.open) < std::abs(*position_.profitTarget - candle.open)) {
                tpHit = false;
            } else {
                slHit = false;
            }
        }

        if (slHit || tpHit) {
            double closePrice = slHit ? *position_.stopLoss : *position_.profitTarget;
            closePosition(closePrice);
        }
    }
}

bool PositionManager::openPosition(const PositionType type, const double price, const std::optional<double> stopLoss, const double sizeFactor) {
// bool PositionManager::openPosition(const double price, const std::optional<double> stopLoss, const double sizeFactor) {
    if (position_.isOpen){ 
        // std::cout << "Not opening new position, already open\n";
        return false;
    }

    // std::cout << "Opening new position\n";
    position_.isOpen = true;
    position_.type = type;
    position_.openPrice = price;
    position_.stopLoss = stopLoss;
    if (position_.stopLoss.has_value() && riskReward_.has_value()) {
        position_.profitTarget = (price - *stopLoss) / *riskReward_;
    }

    position_.sizeFactor = sizeFactor;

    return true;
}

bool PositionManager::closePosition(const double price){
    if (!position_.isOpen){
        // std::cout << "Not closing position, already closed\n";
        return false;
    }

    // std::cout << "Closing position\n";
    position_.isOpen = false;
    // position_.closePrice = price;
    tradeCount_++;

    if(position_.openPrice < price) {
        if(position_.type == PositionType::Long) winCount_++;
        else lossCount_++; 
    } else {
        if(position_.type == PositionType::Long) lossCount_++;
        else winCount_++; 
    }

    return wallet_.updateBalance(position_.priceChangePercentage(), position_.sizeFactor);
}

PositionManagerSnapshot PositionManager::getSnapshot() const noexcept {
    return PositionManagerSnapshot {
        tradeCount_,
        winCount_,
        lossCount_,
        riskPerTrade_
    };
}

WalletSnapshot PositionManager::getWalletSnapshot() const noexcept {
    return wallet_.getSnapshot(); 
}
