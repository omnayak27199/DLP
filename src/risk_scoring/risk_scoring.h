#ifndef RISK_SCORING_H
#define RISK_SCORING_H

enum RiskLevel { LOW, MEDIUM, HIGH, CRITICAL };

class RiskScoring {
public:
    RiskLevel calculateRisk(int sensitivity, int destRisk, int userRisk, int behaviorRisk, int deviceRisk);
};

#endif