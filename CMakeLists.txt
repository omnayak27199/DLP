cmake_minimum_required(VERSION 3.10)
project(DLP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBPCAP REQUIRED libpcap)
pkg_check_modules(OPENSSL REQUIRED openssl)

# Include directories
include_directories(src ${LIBPCAP_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIRS})

# Add subdirectories
add_subdirectory(src/network_sensor)
add_subdirectory(src/policy_engine)
add_subdirectory(src/risk_scoring)
add_subdirectory(src/secret_detection)
add_subdirectory(src/ai_guard)
add_subdirectory(src/dashboard)
add_subdirectory(src/common)
add_subdirectory(src/endpoint_agent)
add_subdirectory(src/analytics_engine)
add_subdirectory(src/saas_connector)
add_subdirectory(src/behavior_analytics)
add_subdirectory(src/sase_integration)
add_subdirectory(tests)

# Main executable or library
add_executable(dlp src/main.cpp)
target_link_libraries(dlp network_sensor policy_engine risk_scoring secret_detection ai_guard dashboard common endpoint_agent analytics_engine saas_connector behavior_analytics sase_integration ${LIBPCAP_LIBRARIES} ${OPENSSL_LIBRARIES})