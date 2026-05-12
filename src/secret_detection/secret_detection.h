#ifndef SECRET_DETECTION_H
#define SECRET_DETECTION_H

#include <string>

class SecretDetection {
public:
    bool detectSecrets(const std::string& data);
private:
    double calculateEntropy(const std::string& str);
};

#endif