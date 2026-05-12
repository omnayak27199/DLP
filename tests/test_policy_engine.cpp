#include <gtest/gtest.h>
#include "../src/policy_engine/policy_engine.h"

TEST(PolicyEngineTest, BlocksSourceCodeToAI) {
    PolicyEngine engine;
    Action action = engine.evaluatePolicy("source_code", "ai");
    EXPECT_EQ(action, BLOCK);
}

TEST(PolicyEngineTest, EncryptsPII) {
    PolicyEngine engine;
    Action action = engine.evaluatePolicy("PII", "external");
    EXPECT_EQ(action, ENCRYPT);
}

TEST(PolicyEngineTest, AllowsNormal) {
    PolicyEngine engine;
    Action action = engine.evaluatePolicy("public", "internal");
    EXPECT_EQ(action, ALLOW);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}