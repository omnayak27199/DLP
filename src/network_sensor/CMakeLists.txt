add_library(network_sensor SHARED network_sensor.cpp)
target_link_libraries(network_sensor ${LIBPCAP_LIBRARIES} ${OPENSSL_LIBRARIES})