#include <gtest/gtest.h>
#include "../src/secret_detection/secret_detection.h"

TEST(SecretDetectionTest, DetectsAWSKey) {
    SecretDetection detector;
    std::string data = "AKIAIOSFODNN7EXAMPLE";
    EXPECT_TRUE(detector.detectSecrets(data));
}

TEST(SecretDetectionTest, DetectsHighEntropy) {
    SecretDetection detector;
    std::string data = "randomstringwithhighentropy1234567890";
    EXPECT_TRUE(detector.detectSecrets(data));
}

TEST(SecretDetectionTest, NoFalsePositive) {
    SecretDetection detector;
    std::string data = "This is normal text";
    EXPECT_FALSE(detector.detectSecrets(data));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}