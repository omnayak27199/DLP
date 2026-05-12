#ifndef POLICY_ENGINE_H
#define POLICY_ENGINE_H

#include <string>

enum Action { ALLOW, WARN, BLOCK, QUARANTINE, ENCRYPT, ALERT };

class PolicyEngine {
public:
    Action evaluatePolicy(const std::string& dataType, const std::string& destination);
};

#endif