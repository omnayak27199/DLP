#ifndef ANALYTICS_ENGINE_H
#define ANALYTICS_ENGINE_H

#include <string>

class AnalyticsEngine {
public:
    void logIncident(const std::string& incident);
    void generateReport();
};

#endif