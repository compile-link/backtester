#include "DataManager.hpp"
#include <gtest/gtest.h>

namespace fs = std::filesystem;

const fs::path fixturesDir = fs::path(PROJECT_SOURCE_DIR) / "tests" / "fixtures";
const fs::path validDataFile = fixturesDir / "valid.csv";
const fs::path invalidDataFile = fixturesDir / "invalid.csv";
const fs::path onlyHeaderDataFile = fixturesDir / "only-header.csv";

namespace {
    class ScopedCwd {
        public:
            explicit ScopedCwd(const fs::path& p) : old_(fs::current_path()) { fs::current_path(p); }
            ~ScopedCwd() { fs::current_path(old_); }
        private:
            fs::path old_;
    };
}

TEST(DataManager, ScanDataDirectoryNoFallbackThrows) {
    // Change cwd to directory without data dir there and in its parent dir (prevent fallback)
    ScopedCwd cwd(fixturesDir / "temp");
    const fs::path nonExistentDataDir = fixturesDir / "non-existent";
    EXPECT_THROW(DataManager dm(nonExistentDataDir.string()), std::runtime_error);
}

TEST(DataManager, LoadValidDataFile) {
    DataManager dm(fixturesDir.string());
    EXPECT_TRUE(dm.loadData(validDataFile.stem()));
    EXPECT_EQ(dm.getCandles().size(), 2u);
}

TEST(DataManager, LoadInvalidDataFileThrows) {
    DataManager dm(fixturesDir.string());
    EXPECT_THROW(dm.loadData(invalidDataFile.stem()), std::runtime_error);
    EXPECT_EQ(dm.getCandles().size(), 0u);
}

TEST(DataManager, LoadNonExistentFileThrows) {
    DataManager dm(fixturesDir.string());
    EXPECT_THROW(dm.loadData("non-existent"), std::out_of_range);
}

TEST(DataManager, LoadOnlyHeaderDataFile) {
    DataManager dm(fixturesDir.string());
    EXPECT_FALSE(dm.loadData(onlyHeaderDataFile.stem()));
    EXPECT_EQ(dm.getCandles().size(), 0u);
}

TEST(DataManager, ReuseDataFile) {
    DataManager dm(fixturesDir.string());
    ASSERT_TRUE(dm.loadData(validDataFile.stem()));
    EXPECT_FALSE(dm.loadData(validDataFile.stem()));
}

TEST(DataManager, SnapshotBeforeLoad) {
    DataManager dm(fixturesDir.string());
    
    auto snapshot = dm.getSnapshot();
    EXPECT_EQ(snapshot.fileName, "");
    EXPECT_EQ(snapshot.startDate, "N/A");
    EXPECT_EQ(snapshot.endDate, "N/A");
    EXPECT_EQ(snapshot.candleCount, 0u);
}

TEST(DataManager, SnapshotAfterValidLoad) {
    DataManager dm(fixturesDir.string());
    ASSERT_TRUE(dm.loadData(validDataFile.stem()));
    
    auto snapshot = dm.getSnapshot();
    EXPECT_EQ(snapshot.fileName, "valid.csv");
    EXPECT_EQ(snapshot.startDate, "2010-07-19");
    EXPECT_EQ(snapshot.endDate, "2010-07-20");
    EXPECT_EQ(snapshot.candleCount, 2u);
}