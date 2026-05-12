#ifndef AI_GUARD_H
#define AI_GUARD_H

#include <string>

class AIGuard {
public:
    bool inspectPrompt(const std::string& prompt, const std::string& destination);
};

#endif