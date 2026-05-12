#include <gtest/gtest.h>
#include "../src/ai_guard/ai_guard.h"

TEST(AIGuardTest, BlocksAIPrompt) {
    AIGuard guard;
    std::string prompt = "Please analyze this source code";
    EXPECT_TRUE(guard.inspectPrompt(prompt, "openai.com"));
}

TEST(AIGuardTest, AllowsNormalPrompt) {
    AIGuard guard;
    std::string prompt = "Hello world";
    EXPECT_FALSE(guard.inspectPrompt(prompt, "example.com"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}