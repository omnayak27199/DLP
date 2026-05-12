#include <iostream>
#include "network_sensor/network_sensor.h"
#include "policy_engine/policy_engine.h"
#include "risk_scoring/risk_scoring.h"
#include "secret_detection/secret_detection.h"
#include "ai_guard/ai_guard.h"
#include "dashboard/dashboard.h"
#include "endpoint_agent/endpoint_agent.h"
#include "analytics_engine/analytics_engine.h"
#include "saas_connector/saas_connector.h"
#include "behavior_analytics/behavior_analytics.h"
#include "sase_integration/sase_integration.h"

int main() {
    std::cout << "DLP Platform Starting..." << std::endl;

    NetworkSensor sensor;
    PolicyEngine policy;
    RiskScoring risk;
    SecretDetection secrets;
    AIGuard aiGuard;
    Dashboard dash;
    EndpointAgent endpoint;
    AnalyticsEngine analytics;
    SaaSConnector saas;
    BehaviorAnalytics behavior;
    SASEIntegration sase;

    // Train a simple behavior baseline
    behavior.trainBaseline({
        {"alice", "upload", "github", 10},
        {"alice", "upload", "github", 12},
        {"alice", "download", "github", 8},
        {"bob", "upload", "dropbox", 50},
    });

    BehaviorAnalytics::Event anomalousEvent{"alice", "upload", "github", 120};
    if (behavior.isAnomalous(anomalousEvent)) {
        std::cout << "Behavior anomaly detected for user " << anomalousEvent.user << std::endl;
        analytics.logIncident("Behavior anomaly detected for alice");
    }

    // Start network sensor
    sensor.startCapture("lo"); // Use loopback for demo

    // Start endpoint agent
    endpoint.startMonitoring();

    // Enable SASE features
    sase.enableVPN();
    sase.integrateSDWAN();

    // Example usage
    dash.displayIncidents();
    analytics.logIncident("Test incident");
    saas.sendToSlack("Alert!");

    std::string testData = "This is a test with AKIAIOSFODNN7EXAMPLE";
    if (secrets.detectSecrets(testData)) {
        std::cout << "Secret detected!" << std::endl;
    }

    std::string prompt = "Please analyze this source code";
    if (aiGuard.inspectPrompt(prompt, "openai.com")) {
        std::cout << "AI prompt blocked!" << std::endl;
    }

    Action action = policy.evaluatePolicy("source_code", "ai");
    std::cout << "Policy action: " << action << std::endl;

    RiskLevel level = risk.calculateRisk(5, 5, 3, 2, 1);
    std::cout << "Risk level: " << level << std::endl;

    return 0;
}