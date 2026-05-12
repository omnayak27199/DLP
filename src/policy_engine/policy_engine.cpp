#include "policy_engine.h"
#include <string>
#include <iostream>

Action PolicyEngine::evaluatePolicy(const std::string& dataType, const std::string& destination) {
    if (dataType == "source_code" && destination.find("ai") != std::string::npos) {
        return BLOCK;
    }
    if (dataType == "PII" && destination.find("external") != std::string::npos) {
        return ENCRYPT;
    }
    return ALLOW;
}