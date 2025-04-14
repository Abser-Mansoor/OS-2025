#include <string>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include "message_processor.hpp"

MessageProcessor::MessageProcessor(MessageQueue& queue, ThreadSafeData& data) : queue_(queue), shared_data_(data) {}

void MessageProcessor::processMessages() {
    while(true) {
        auto [client_fd, message] = queue_.pop(); // Consumer: Takes messages from queue
        std::string response;

        if (message == "READ") {
            response = "DATA " + std::to_string(shared_data_.read()) + "\n";
        }

        else if (message == "WRITE") {
            int current = shared_data_.read();
            shared_data_.write(current+1);
            response = "UPDATED: " + std::to_string(current+1) + "\n";
        }

        else {
            response = "ERROR: Invalid request\n";
        }
        if (send(client_fd, response.c_str(), response.size(), 0) == -1) {
            std::cerr << "Send error\n";
        }
        close(client_fd); 
    }
}