#include "network_sensor.h"
#include "../secret_detection/secret_detection.h"
#include "../ai_guard/ai_guard.h"
#include "../policy_engine/policy_engine.h"
#include "../risk_scoring/risk_scoring.h"
#include "../behavior_analytics/behavior_analytics.h"
#include <iostream>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <cstring>

void NetworkSensor::startCapture(const std::string& interfaceName) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_live(interfaceName.c_str(), BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr) {
        std::cerr << "Error opening device: " << errbuf << std::endl;
        return;
    }
    std::cout << "Network sensor started capturing on " << interfaceName << std::endl;
    
    // Start the packet processing loop
    pcap_loop(handle, 0, packetHandler, reinterpret_cast<u_char*>(this));
    
    pcap_close(handle);
}

void NetworkSensor::packetHandler(u_char *userData, const struct pcap_pkthdr *pkthdr, const u_char *packet) {
    NetworkSensor* sensor = reinterpret_cast<NetworkSensor*>(userData);
    sensor->processPacket(pkthdr, packet);
}

void NetworkSensor::processPacket(const struct pcap_pkthdr *pkthdr, const u_char *packet) {
    if (pkthdr->caplen < sizeof(struct ether_header)) {
        return; // Too short to contain an Ethernet header
    }

    struct ether_header *ethHeader = (struct ether_header *)packet;
    if (ntohs(ethHeader->ether_type) != ETHERTYPE_IP) {
        return; // Not an IPv4 packet
    }

    int etherHeaderLen = sizeof(struct ether_header);
    if (pkthdr->caplen < etherHeaderLen + sizeof(struct ip)) {
        return; // Too short to contain an IP header
    }

    const u_char *ipHeaderData = packet + etherHeaderLen;
    struct ip *ipHeader = (struct ip *)(ipHeaderData);
    
    if (ipHeader->ip_p != IPPROTO_TCP) {
        return; // Not a TCP packet
    }

    int ipHeaderLen = ipHeader->ip_hl * 4;
    int tcpOffset = etherHeaderLen + ipHeaderLen;
    
    if (pkthdr->caplen < tcpOffset + 20) { // TCP header is at least 20 bytes
        return;
    }

    const u_char *tcpHeaderData = packet + tcpOffset;
    uint16_t srcPort = ntohs(*(uint16_t*)(tcpHeaderData));
    uint16_t dstPort = ntohs(*(uint16_t*)(tcpHeaderData + 2));
    int tcpHeaderLen = ((tcpHeaderData[12] >> 4) & 0x0F) * 4;
    
    int payloadOffset = tcpOffset + tcpHeaderLen;
    int payloadLength = pkthdr->len - payloadOffset;

    if (payloadLength <= 0 || pkthdr->caplen < payloadOffset) {
        return; // No payload
    }

    const u_char *payload = packet + payloadOffset;
    
    // Cap payload length to captured length to prevent out of bounds reading
    int capPayloadLength = pkthdr->caplen - payloadOffset;
    if (payloadLength > capPayloadLength) {
        payloadLength = capPayloadLength;
    }

    if (dstPort == 80 || srcPort == 80 || dstPort == 8080 || srcPort == 8080) {
        parseHTTP(payload, payloadLength);
    } else if (dstPort == 443 || srcPort == 443) {
        parseHTTPS(payload, payloadLength);
    }
}

void NetworkSensor::parseHTTP(const u_char *payload, int payloadLength) {
    std::cout << "[Network Sensor] HTTP traffic detected (" << payloadLength << " bytes)." << std::endl;
    extractFiles(payload, payloadLength);
}

void NetworkSensor::parseHTTPS(const u_char *payload, int payloadLength) {
    // In a real implementation, this would involve TLS decryption/inspection
    std::cout << "[Network Sensor] Encrypted HTTPS traffic detected (" << payloadLength << " bytes)." << std::endl;
}

void NetworkSensor::extractFiles(const u_char *payload, int payloadLength) {
    std::string payloadStr(reinterpret_cast<const char*>(payload), payloadLength);
    
    // Basic heuristics for file transfers
    if (payloadStr.find("Content-Disposition: attachment") != std::string::npos || 
        payloadStr.find("Content-Type: application/") != std::string::npos ||
        payloadStr.find("Content-Type: multipart/form-data") != std::string::npos) {
        std::cout << "[Network Sensor] Potential file transfer extracted." << std::endl;
        runInspectionPipeline(payloadStr);
    }
}

void NetworkSensor::runInspectionPipeline(const std::string& extractedData) {
    std::cout << "[Inspection Pipeline] Initiating full inspection on extracted data..." << std::endl;
    
    SecretDetection secretEngine;
    AIGuard aiEngine;
    PolicyEngine policyEngine;
    RiskScoring riskEngine;
    BehaviorAnalytics behaviorEngine;
    
    // Detect secrets
    if (secretEngine.detectSecrets(extractedData)) {
        std::cout << "[Inspection] Secrets detected!" << std::endl;
    }
    
    // Check AI prompts (assume destination is AI if contains certain keywords)
    if (aiEngine.inspectPrompt(extractedData, "ai-service")) {
        std::cout << "[Inspection] AI prompt blocked!" << std::endl;
    }
    
    // Evaluate policy
    Action action = policyEngine.evaluatePolicy("data", "destination");
    std::cout << "[Inspection] Policy action: " << action << std::endl;
    
    // Calculate risk
    RiskLevel risk = riskEngine.calculateRisk(5, 5, 3, 2, 1);
    std::cout << "[Inspection] Risk level: " << risk << std::endl;

    // Train a lightweight behavior baseline and score the current event
    behaviorEngine.trainBaseline({
        {"alice", "upload", "github", 10},
        {"alice", "upload", "github", 12},
        {"alice", "download", "github", 8},
        {"bob", "upload", "dropbox", 50},
    });

    BehaviorAnalytics::Event currentEvent{"unknown", "upload", "github", static_cast<int>(extractedData.size())};
    if (behaviorEngine.isAnomalous(currentEvent)) {
        std::cout << "[Behavior Analytics] Anomalous behavior detected for event size=" << extractedData.size() << std::endl;
    }
}
