#include "Wallet.hpp"
#include <gtest/gtest.h>

TEST(Wallet, DefaultSnapshot) {
    Wallet w{10000.0};
    WalletSnapshot ws = w.getSnapshot();

    EXPECT_EQ(ws.initialBalance, 10000.0);
    EXPECT_EQ(ws.endBalance, 10000.0);
    EXPECT_EQ(ws.pnL, 0.0);
}

TEST(Wallet, UpdateBalance) {
    Wallet w{5000.0};
    w.updateBalance(1.4);

    WalletSnapshot ws = w.getSnapshot();
    EXPECT_EQ(ws.endBalance, 12000.0);
    EXPECT_EQ(ws.pnL, 7000.0);
    
    w.updateBalance(-0.5);
    ws = w.getSnapshot();
    
    EXPECT_EQ(ws.endBalance, 6000.0);
    EXPECT_EQ(ws.pnL, 1000.0);
}

TEST(Wallet, Reset) {
    Wallet w{10000.0};
    w.updateBalance(0.7);

    WalletSnapshot ws = w.getSnapshot();
    ASSERT_EQ(ws.endBalance, 17000.0);
    ASSERT_EQ(ws.pnL, 7000.0);
    
    w.reset();
    ws = w.getSnapshot();
    EXPECT_EQ(ws.endBalance, 10000.0);
    EXPECT_EQ(ws.pnL, 0.0);
}