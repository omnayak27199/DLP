#include <gtest/gtest.h>
#include "../src/risk_scoring/risk_scoring.h"

TEST(RiskScoringTest, CalculatesHighRisk) {
    RiskScoring scorer;
    RiskLevel level = scorer.calculateRisk(5, 5, 5, 5, 5);
    EXPECT_EQ(level, CRITICAL);
}

TEST(RiskScoringTest, CalculatesLowRisk) {
    RiskScoring scorer;
    RiskLevel level = scorer.calculateRisk(1, 1, 1, 1, 1);
    EXPECT_EQ(level, LOW);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}