#include "endpoint_agent.h"
#include <iostream>
#include <sys/inotify.h>
#include <unistd.h>
#include <cstring>

void EndpointAgent::startMonitoring() {
    std::cout << "Endpoint Agent starting monitoring..." << std::endl;
    monitorUSB();
    monitorClipboard();
    monitorFileAccess("/tmp"); // Example path
}

void EndpointAgent::monitorUSB() {
    std::cout << "[Endpoint] Monitoring USB devices..." << std::endl;
    // In a real implementation, use libusb or udev
    // For demo, just log
}

void EndpointAgent::monitorClipboard() {
    std::cout << "[Endpoint] Monitoring clipboard..." << std::endl;
    // Use X11 or Wayland APIs, but for simplicity, skip
}

void EndpointAgent::monitorFileAccess(const std::string& path) {
    int fd = inotify_init();
    if (fd < 0) {
        std::cerr << "inotify_init failed" << std::endl;
        return;
    }
    
    int wd = inotify_add_watch(fd, path.c_str(), IN_ACCESS | IN_MODIFY | IN_CLOSE_WRITE);
    if (wd < 0) {
        std::cerr << "inotify_add_watch failed" << std::endl;
        close(fd);
        return;
    }
    
    std::cout << "[Endpoint] Monitoring file access on " << path << std::endl;
    
    char buffer[1024];
    while (true) {
        int length = read(fd, buffer, sizeof(buffer));
        if (length < 0) {
            std::cerr << "read failed" << std::endl;
            break;
        }
        
        int i = 0;
        while (i < length) {
            struct inotify_event *event = (struct inotify_event *)&buffer[i];
            if (event->len) {
                std::cout << "[Endpoint] File event: " << event->name << std::endl;
                // Run inspection on file content
            }
            i += sizeof(struct inotify_event) + event->len;
        }
    }
    
    inotify_rm_watch(fd, wd);
    close(fd);
}