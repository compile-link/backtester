#include "DataManager.hpp"
#include "PositionManager.hpp"
#include "Strategies/Strategy.hpp"
#include <gtest/gtest.h>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

namespace {
    const fs::path fixturesDir = fs::path(PROJECT_SOURCE_DIR) / "tests" / "fixtures";

    class StubStrategy : public Strategy {
        public:
            explicit StubStrategy(std::vector<Signal> signals): signals_(signals) {}

            Signal onCandle(const Candle&, std::optional<double>& stopLoss) override {
                stopLoss = std::nullopt;
                Signal s = (idx_ >= signals_.size()) ? Signal::Wait : signals_[idx_];
                ++idx_;
                return s;
            }

            std::string_view name() const noexcept override { return "StubStrategy"; }
            void description() const noexcept override {}

        private:
            std::vector<Signal> signals_;
            size_t idx_ = 0;
    };
}

TEST(BacktestFlow, DataManagerStrategyPositionManagerFlow) {
    DataManager dm(fixturesDir.string());
    ASSERT_TRUE(dm.loadData("valid"));

    PositionManager pm;
    pm.setRisk(std::nullopt); // unamanaged risk mode
    StubStrategy strategy({Signal::Buy, Signal::Sell});
    std::vector<double> candleCloses;
    candleCloses.reserve(dm.getCandles().size());

    for (const auto& c: dm.getCandles()) {
        std::optional<double> sl = std::nullopt;
        Signal s = strategy.onCandle(c, sl);
        pm.onCandle(c, s, sl);
        candleCloses.push_back(c.close);
    }

    const auto pms = pm.getSnapshot();
    const auto ws = pm.getWalletSnapshot();

    EXPECT_EQ(pms.tradeCount, 1u);
    EXPECT_EQ(pms.winCount, 0u);
    EXPECT_EQ(pms.lossCount, 1u);

    ASSERT_TRUE(candleCloses.size() >= 2u);
    const auto a = candleCloses[0];
    const auto b = candleCloses[1];
    const auto diff = (b - a) / a;
    const auto expectedBalance = 10000 + (10000.0 * diff);
    EXPECT_NEAR(ws.endBalance, expectedBalance, 1e-9);
}
