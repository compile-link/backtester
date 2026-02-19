#include "PositionManager.hpp"
#include <gtest/gtest.h>

TEST(PositionManager, Snapshot) {
    PositionManager pm{};
    pm.setRisk(std::nullopt);
    PositionManagerSnapshot pms = pm.getSnapshot();
    WalletSnapshot ws = pm.getWalletSnapshot();
    
    EXPECT_EQ(pms.tradeCount, 0u);
    EXPECT_EQ(pms.winCount, 0u);
    EXPECT_EQ(pms.lossCount, 0u);
    EXPECT_EQ(pms.riskPerTrade, std::nullopt);
    EXPECT_EQ(ws.endBalance, 10000.0);
}

TEST(PositionManager, LongTradeWin) {
    PositionManager pm{};
    pm.setRisk(std::nullopt);
    PositionManagerSnapshot pms = pm.getSnapshot();
    WalletSnapshot ws = pm.getWalletSnapshot();

    ASSERT_EQ(pms.tradeCount, 0u);
    ASSERT_EQ(pms.winCount, 0u);
    ASSERT_EQ(pms.lossCount, 0u);
    ASSERT_EQ(pms.riskPerTrade, std::nullopt);
    ASSERT_EQ(ws.endBalance, 10000.0);

    EXPECT_TRUE(pm.openLong(100.0));
    EXPECT_TRUE(pm.closeLong(130.0));
    pms = pm.getSnapshot();
    ws = pm.getWalletSnapshot();
    
    EXPECT_EQ(pms.tradeCount, 1u);
    EXPECT_EQ(pms.winCount, 1u);
    EXPECT_EQ(pms.lossCount, 0u);
    EXPECT_EQ(ws.endBalance, 13000.0);
}

TEST(PositionManager, LongTradeLoss) {
    PositionManager pm{};
    pm.setRisk(std::nullopt);
    PositionManagerSnapshot pms = pm.getSnapshot();
    WalletSnapshot ws = pm.getWalletSnapshot();

    ASSERT_EQ(pms.tradeCount, 0u);
    ASSERT_EQ(pms.winCount, 0u);
    ASSERT_EQ(pms.lossCount, 0u);
    ASSERT_EQ(pms.riskPerTrade, std::nullopt);
    ASSERT_EQ(ws.endBalance, 10000.0);

    EXPECT_TRUE(pm.openLong(100.0));
    EXPECT_TRUE(pm.closeLong(70.0));
    pms = pm.getSnapshot();
    ws = pm.getWalletSnapshot();
    
    EXPECT_EQ(pms.tradeCount, 1u);
    EXPECT_EQ(pms.winCount, 0u);
    EXPECT_EQ(pms.lossCount, 1u);
    EXPECT_EQ(ws.endBalance, 7000.0);
}

TEST(PositionManager, ShortTradeWin) {
    PositionManager pm{};
    pm.setRisk(std::nullopt);
    PositionManagerSnapshot pms = pm.getSnapshot();
    WalletSnapshot ws = pm.getWalletSnapshot();

    ASSERT_EQ(pms.tradeCount, 0u);
    ASSERT_EQ(pms.winCount, 0u);
    ASSERT_EQ(pms.lossCount, 0u);
    ASSERT_EQ(pms.riskPerTrade, std::nullopt);
    ASSERT_EQ(ws.endBalance, 10000.0);

    EXPECT_TRUE(pm.openShort(100.0));
    EXPECT_TRUE(pm.closeShort(70.0));
    pms = pm.getSnapshot();
    ws = pm.getWalletSnapshot();
    
    EXPECT_EQ(pms.tradeCount, 1u);
    EXPECT_EQ(pms.winCount, 1u);
    EXPECT_EQ(pms.lossCount, 0u);
    EXPECT_EQ(ws.endBalance, 13000.0);
}

TEST(PositionManager, ShortTradeLoss) {
    PositionManager pm{};
    pm.setRisk(std::nullopt);
    PositionManagerSnapshot pms = pm.getSnapshot();
    WalletSnapshot ws = pm.getWalletSnapshot();

    ASSERT_EQ(pms.tradeCount, 0u);
    ASSERT_EQ(pms.winCount, 0u);
    ASSERT_EQ(pms.lossCount, 0u);
    ASSERT_EQ(pms.riskPerTrade, std::nullopt);
    ASSERT_EQ(ws.endBalance, 10000.0);

    EXPECT_TRUE(pm.openShort(100.0));
    EXPECT_TRUE(pm.closeShort(130.0));
    pms = pm.getSnapshot();
    ws = pm.getWalletSnapshot();
    
    EXPECT_EQ(pms.tradeCount, 1u);
    EXPECT_EQ(pms.winCount, 0u);
    EXPECT_EQ(pms.lossCount, 1u);
    EXPECT_EQ(ws.endBalance, 7000.0);
}

TEST(PositionManager, FailToOpenWhenAlreadyOpen) {
    PositionManager pm{};

    ASSERT_TRUE(pm.openShort(100.0));
    EXPECT_FALSE(pm.openShort(110.0));
}

TEST(PositionManager, FailToOpenWithNonPositivePrice) {
    PositionManager pm{};

    EXPECT_FALSE(pm.openLong(-100.0));
    EXPECT_FALSE(pm.openLong(0.0));
}

TEST(PositionManager, FailToCloseWithoutOpen) {
    PositionManager pm{};

    EXPECT_FALSE(pm.closeLong(100.0));
}

TEST(PositionManager, OnCandleStopLoss) {
    PositionManager pm{};
    pm.setRisk(0.5);

    pm.openLong(100.0, 90.0);
    
    PositionManagerSnapshot pms = pm.getSnapshot();
    WalletSnapshot ws = pm.getWalletSnapshot();

    ASSERT_EQ(pms.tradeCount, 0u);
    ASSERT_EQ(pms.winCount, 0u);
    ASSERT_EQ(pms.lossCount, 0u);
    ASSERT_EQ(pms.riskPerTrade, 1.0);
    ASSERT_EQ(ws.endBalance, 10000.0);


    Candle c = { "2010-10-10", 101.0, 112.0, 89.0, 105.0 };
    pm.onCandle(c, Signal::Wait, std::nullopt);
    pms = pm.getSnapshot();
    ws = pm.getWalletSnapshot();
    
    EXPECT_EQ(pms.tradeCount, 1u);
    EXPECT_EQ(pms.winCount, 0u);
    EXPECT_EQ(pms.lossCount, 1u);
    EXPECT_EQ(ws.endBalance, 9900.0);    
}

TEST(PositionManager, OnCandleNoStopLoss) {
    PositionManager pm{};
    pm.setRisk(std::nullopt);

    pm.openLong(100.0);
    
    PositionManagerSnapshot pms = pm.getSnapshot();
    WalletSnapshot ws = pm.getWalletSnapshot();

    ASSERT_EQ(pms.tradeCount, 0u);
    ASSERT_EQ(pms.winCount, 0u);
    ASSERT_EQ(pms.lossCount, 0u);
    ASSERT_EQ(pms.riskPerTrade, std::nullopt);
    ASSERT_EQ(ws.endBalance, 10000.0);


    double close = 105.0;
    Candle c = { "2010-10-10", 101.0, 112.0, 89.0, close };
    pm.onCandle(c, Signal::Sell, std::nullopt);
    pms = pm.getSnapshot();
    ws = pm.getWalletSnapshot();
    
    EXPECT_EQ(pms.tradeCount, 1u);
    EXPECT_EQ(pms.winCount, 1u);
    EXPECT_EQ(pms.lossCount, 0u);
    EXPECT_EQ(ws.endBalance, 10500.0);    
}

TEST(PositionManager, ResetClearsAll) {
    PositionManager pm{};
    pm.setRisk(std::nullopt);

    Candle c1 = { "2010-10-11", 101.0, 112.0, 89.0, 100.0 };
    Candle c2 = { "2010-10-12", 105.0, 117.0, 100.0, 110.0 };
    Candle c3 = { "2010-10-13", 109.0, 121.0, 108.0, 115.5 };

    PositionManagerSnapshot pms = pm.getSnapshot();
    WalletSnapshot ws = pm.getWalletSnapshot();

    ASSERT_EQ(pms.tradeCount, 0u);
    ASSERT_EQ(pms.winCount, 0u);
    ASSERT_EQ(pms.lossCount, 0u);
    ASSERT_EQ(pms.riskPerTrade, std::nullopt);
    ASSERT_EQ(ws.endBalance, 10000.0);

    pm.onCandle(c1, Signal::Buy, std::nullopt);
    pm.onCandle(c2, Signal::Sell, std::nullopt);
    pms = pm.getSnapshot();
    ws = pm.getWalletSnapshot();

    ASSERT_EQ(pms.tradeCount, 1u);
    ASSERT_EQ(pms.winCount, 1u);
    ASSERT_EQ(pms.lossCount, 0u);
    ASSERT_EQ(ws.endBalance, 11000.0);    

    pm.onCandle(c3, Signal::Buy, std::nullopt);
    pms = pm.getSnapshot();
    ws = pm.getWalletSnapshot();

    ASSERT_EQ(pms.tradeCount, 2u);
    ASSERT_EQ(pms.winCount, 1u);
    ASSERT_EQ(pms.lossCount, 1u);
    ASSERT_EQ(ws.endBalance, 10450.0);    
    
    pm.reset();
    pms = pm.getSnapshot();
    ws = pm.getWalletSnapshot();

    EXPECT_EQ(pms.tradeCount, 0u);
    EXPECT_EQ(pms.winCount, 0u);
    EXPECT_EQ(pms.lossCount, 0u);
    EXPECT_EQ(ws.endBalance, 10000.0);    
}

TEST(PositionManager, OnCandleStopLossAndProfitTargetHit) {
    PositionManager pm{};
    pm.setRisk(0.5);

    pm.openLong(100.0, 95.0);
    
    PositionManagerSnapshot pms = pm.getSnapshot();
    WalletSnapshot ws = pm.getWalletSnapshot();

    ASSERT_EQ(pms.tradeCount, 0u);
    ASSERT_EQ(pms.winCount, 0u);
    ASSERT_EQ(pms.lossCount, 0u);
    ASSERT_EQ(pms.riskPerTrade, 1.0);
    ASSERT_EQ(ws.endBalance, 10000.0);


    Candle c = { "2010-10-10", 101.0, 112.0, 89.0, 105.0 };
    pm.onCandle(c, Signal::Wait, std::nullopt);
    pms = pm.getSnapshot();
    ws = pm.getWalletSnapshot();
    
    EXPECT_EQ(pms.tradeCount, 1u);
    EXPECT_EQ(pms.winCount, 0u);
    EXPECT_EQ(pms.lossCount, 1u);
    EXPECT_EQ(ws.endBalance, 9900.0);    
}