#ifndef BEHAVIOR_ANALYTICS_H
#define BEHAVIOR_ANALYTICS_H

#include <map>
#include <string>
#include <vector>

class BehaviorAnalytics {
public:
    struct Event {
        std::string user;
        std::string action;
        std::string target;
        int volume;
    };

    void trainBaseline(const std::vector<Event>& events);
    double scoreAnomaly(const Event& event);
    bool isAnomalous(const Event& event, double threshold = 2.0);

private:
    void updateModel(const Event& event);
    double normalizeScore(double score) const;

    std::map<std::string, double> meanVolumeByKey;
    std::map<std::string, double> varianceByKey;
    std::map<std::string, int> countByKey;
};

#endif