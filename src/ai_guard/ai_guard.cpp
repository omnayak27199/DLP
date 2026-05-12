#include "ai_guard.h"
#include <string>
#include <iostream>

bool AIGuard::inspectPrompt(const std::string& prompt, const std::string& destination) {
    // Check if destination is AI service
    if (destination.find("openai.com") != std::string::npos ||
        destination.find("anthropic.com") != std::string::npos) {
        // Check for sensitive content
        if (prompt.find("source code") != std::string::npos ||
            prompt.find("AWS key") != std::string::npos) {
            std::cout << "AI prompt leakage detected" << std::endl;
            return true; // Block
        }
    }
    return false;
}