# DLP

Next-Generation Modular DLP Platform

## Vision

Build a high-performance, modular, developer-friendly DLP platform optimized for enterprises, MSP/SASE providers, SD-WAN deployments, hybrid cloud environments, and AI/SaaS traffic protection.

## Key Features

- Agentless-first architecture
- Modular licensing
- High-performance C/C++ packet engine
- Kubernetes support
- Multi-tenant
- AI prompt inspection
- Context-aware engine with low false positives

## Architecture

Modular design with independent modules:

- Network Sensor
- Policy Engine
- Risk Scoring
- Secret Detection
- AI Guard
- Dashboard
- Endpoint Agent
- Analytics Engine
- SaaS Connector
- Behavior Analytics
- SASE Integration

## User Manual

### Installation

#### Prerequisites
- Linux system (Ubuntu/Debian recommended)
- CMake 3.10+
- GCC/G++ 7+
- libpcap-dev
- libssl-dev

#### Build Instructions
```bash
sudo apt update
sudo apt install -y build-essential cmake libpcap-dev libssl-dev
cd /workspaces/DLP
mkdir build
cd build
cmake ..
make
```

#### Installation on Server/Router
For Linux servers:
```bash
sudo make install  # Installs to /usr/local/bin
```

For routers (cross-compile if needed):
- Identify target architecture (e.g., arm64)
- Use appropriate toolchain
- Build statically: `cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF`
- Transfer binary to router via SCP
- Run with appropriate permissions

### Usage

#### Running the Platform
```bash
./dlp
```

#### Configuration
- Edit source code for custom policies (future: config files)
- Interfaces: Default eth0, change in code
- Logs: incidents.log in current directory

#### Modules
- **Network Sensor**: Captures and inspects network traffic
- **Endpoint Agent**: Monitors file access and USB
- **AI Guard**: Protects against AI prompt leakage
- **Secret Detection**: Detects secrets via regex and entropy
- **Policy Engine**: Enforces data handling rules
- **Risk Scoring**: Calculates risk levels
- **Behavior Analytics**: Detects anomalous user behavior
- **Analytics Engine**: Logs incidents and generates reports
- **SaaS Connector**: Integrates with Slack/GitHub
- **SASE Integration**: VPN and SD-WAN features

### Troubleshooting
- Permission denied: Run as root or with CAP_NET_RAW
- Build errors: Ensure all dependencies installed
- No traffic: Check interface name and permissions

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Running Tests

```bash
cd build
make
./tests/test_secret_detection
./tests/test_ai_guard
./tests/test_policy_engine
./tests/test_risk_scoring
./tests/test_behavior_analytics
```

Or use CTest:
```bash
ctest
```