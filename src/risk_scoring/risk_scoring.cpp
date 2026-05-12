#include "risk_scoring.h"
#include <iostream>

RiskLevel RiskScoring::calculateRisk(int sensitivity, int destRisk, int userRisk, int behaviorRisk, int deviceRisk) {
    int total = sensitivity + destRisk + userRisk + behaviorRisk + deviceRisk;
    if (total > 15) return CRITICAL;
    if (total > 10) return HIGH;
    if (total > 5) return MEDIUM;
    return LOW;
}