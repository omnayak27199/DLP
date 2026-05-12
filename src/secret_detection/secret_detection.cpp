#include "secret_detection.h"
#include <regex>
#include <string>
#include <iostream>
#include <cmath>
#include <map>

bool SecretDetection::detectSecrets(const std::string& data) {
    // Simple regex for AWS keys
    std::regex awsKeyRegex("AKIA[0-9A-Z]{16}");
    if (std::regex_search(data, awsKeyRegex)) {
        std::cout << "Potential AWS key detected" << std::endl;
        return true;
    }
    
    // Entropy analysis for random strings
    if (calculateEntropy(data) > 4.0) { // Threshold for high entropy
        std::cout << "High entropy string detected, possible secret" << std::endl;
        return true;
    }
    
    // TODO: Add more patterns
    return false;
}

double SecretDetection::calculateEntropy(const std::string& str) {
    std::map<char, int> freq;
    for (char c : str) {
        freq[c]++;
    }
    double entropy = 0.0;
    for (auto& p : freq) {
        double prob = static_cast<double>(p.second) / str.length();
        entropy -= prob * log2(prob);
    }
    return entropy;
}