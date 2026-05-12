#include "behavior_analytics.h"
#include <cmath>
#include <iostream>
#include <map>

void BehaviorAnalytics::trainBaseline(const std::vector<Event>& events) {
    for (const auto& event : events) {
        updateModel(event);
    }
    std::cout << "[Behavior Analytics] Baseline trained on " << events.size() << " events." << std::endl;
}

double BehaviorAnalytics::scoreAnomaly(const Event& event) {
    std::string key = event.user + ":" + event.action + ":" + event.target;
    auto meanIt = meanVolumeByKey.find(key);
    auto varIt = varianceByKey.find(key);
    if (meanIt == meanVolumeByKey.end() || varIt == varianceByKey.end()) {
        // Unknown behavior is treated as suspicious.
        return 3.0;
    }

    double mean = meanIt->second;
    double variance = varIt->second;
    double stddev = std::sqrt(variance);
    if (stddev < 1.0) {
        stddev = 1.0;
    }

    double z = std::fabs(event.volume - mean) / stddev;
    return normalizeScore(z);
}

bool BehaviorAnalytics::isAnomalous(const Event& event, double threshold) {
    double score = scoreAnomaly(event);
    std::cout << "[Behavior Analytics] Event score=" << score << " for user=" << event.user
              << " action=" << event.action << " target=" << event.target << std::endl;
    return score >= threshold;
}

void BehaviorAnalytics::updateModel(const Event& event) {
    std::string key = event.user + ":" + event.action + ":" + event.target;
    int count = countByKey[key];
    double mean = meanVolumeByKey[key];
    double variance = varianceByKey[key];
    
    count += 1;
    double delta = event.volume - mean;
    mean += delta / count;
    variance += delta * (event.volume - mean);

    countByKey[key] = count;
    meanVolumeByKey[key] = mean;
    varianceByKey[key] = variance / count;
}

double BehaviorAnalytics::normalizeScore(double score) const {
    if (score > 5.0) return 5.0;
    return score;
}