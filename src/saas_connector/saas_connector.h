#ifndef SAAS_CONNECTOR_H
#define SAAS_CONNECTOR_H

#include <string>

class SaaSConnector {
public:
    void sendToSlack(const std::string& message);
    void sendToGitHub(const std::string& data);
};

#endif