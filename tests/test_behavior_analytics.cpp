#include <gtest/gtest.h>
#include "../src/behavior_analytics/behavior_analytics.h"

TEST(BehaviorAnalyticsTest, DetectsAnomaly) {
    BehaviorAnalytics analytics;
    std::vector<BehaviorAnalytics::Event> baseline = {
        {"alice", "upload", "github", 10},
        {"alice", "upload", "github", 12}
    };
    analytics.trainBaseline(baseline);
    
    BehaviorAnalytics::Event anomaly{"alice", "upload", "github", 100};
    EXPECT_TRUE(analytics.isAnomalous(anomaly));
}

TEST(BehaviorAnalyticsTest, NoAnomaly) {
    BehaviorAnalytics analytics;
    std::vector<BehaviorAnalytics::Event> baseline = {
        {"alice", "upload", "github", 10},
        {"alice", "upload", "github", 12}
    };
    analytics.trainBaseline(baseline);
    
    BehaviorAnalytics::Event normal{"alice", "upload", "github", 11};
    EXPECT_FALSE(analytics.isAnomalous(normal));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}