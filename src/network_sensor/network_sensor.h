#ifndef NETWORK_SENSOR_H
#define NETWORK_SENSOR_H

#include <pcap.h>
#include <string>
#include <vector>

class NetworkSensor {
public:
    void startCapture(const std::string& interfaceName = "eth0");

private:
    static void packetHandler(u_char *userData, const struct pcap_pkthdr *pkthdr, const u_char *packet);
    void processPacket(const struct pcap_pkthdr *pkthdr, const u_char *packet);
    
    // Phase 1 enhancements
    void parseHTTP(const u_char *payload, int payloadLength);
    void parseHTTPS(const u_char *payload, int payloadLength);
    void extractFiles(const u_char *payload, int payloadLength);
    void runInspectionPipeline(const std::string& extractedData);
};

#endif