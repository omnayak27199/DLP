cmake_minimum_required(VERSION 3.10)
project(DLPTests)

# Find Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add test executables
add_executable(test_secret_detection test_secret_detection.cpp)
target_link_libraries(test_secret_detection secret_detection ${GTEST_LIBRARIES} pthread)

add_executable(test_ai_guard test_ai_guard.cpp)
target_link_libraries(test_ai_guard ai_guard ${GTEST_LIBRARIES} pthread)

add_executable(test_policy_engine test_policy_engine.cpp)
target_link_libraries(test_policy_engine policy_engine ${GTEST_LIBRARIES} pthread)

add_executable(test_risk_scoring test_risk_scoring.cpp)
target_link_libraries(test_risk_scoring risk_scoring ${GTEST_LIBRARIES} pthread)

add_executable(test_behavior_analytics test_behavior_analytics.cpp)
target_link_libraries(test_behavior_analytics behavior_analytics ${GTEST_LIBRARIES} pthread)

# Enable testing
enable_testing()
add_test(NAME SecretDetectionTest COMMAND test_secret_detection)
add_test(NAME AIGuardTest COMMAND test_ai_guard)
add_test(NAME PolicyEngineTest COMMAND test_policy_engine)
add_test(NAME RiskScoringTest COMMAND test_risk_scoring)
add_test(NAME BehaviorAnalyticsTest COMMAND test_behavior_analytics)