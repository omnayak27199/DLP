#ifndef ENDPOINT_AGENT_H
#define ENDPOINT_AGENT_H

#include <string>

class EndpointAgent {
public:
    void startMonitoring();
    void monitorUSB();
    void monitorClipboard();
    void monitorFileAccess(const std::string& path);
};

#endif