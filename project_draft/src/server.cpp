#include "connection_handler.hpp"
#include "thread_safe_data.hpp"
#include "message_processor.hpp"
#include "socket.hpp"
#include <iostream>
#include <thread>
#include <vector>
#include <memory>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <cstring>
#include <cerrno>

int main() {
    try {
        ThreadSafeData shared_data;
        MessageQueue message_queue;

        std::vector<std::thread> processors;
        for (unsigned i = 0; i < std::thread::hardware_concurrency(); i++) {
            processors.emplace_back([&] {
                MessageProcessor processor(message_queue, shared_data);
                processor.processMessages();
            });
        }

        // Creates TCP socket, AF_INET = IPv4, SOCK_STREAM = TCP
        os_socket::Socket server(AF_INET, SOCK_STREAM, 0);
        server.bind(8080);
        server.listen(); // Default value is 10
        ConnectionHandler handler(message_queue);

        std::cout << "Server running on port 8080...\n";

        std::vector<std::thread> workers;
        std::atomic<bool> running{true};

        // Worker thread function
        auto worker = [&]() {
            while (running) {
                try {
                    auto [client_fd, client_ip] = server.accept();
                    std::cout << "New connection from: " << client_ip << "\n";
                    handler.handle(client_fd);
                } 
                catch (const std::exception& e) {
                    if (running) {
                        std::cerr << "Accept error: " << e.what() << "\n";
                    }
                }
            }
        };

        // Start worker threads
        // hardware_concurrency: Creates one thread per cpu core
        unsigned num_threads = std::thread::hardware_concurrency();
        for (unsigned i = 0; i < num_threads; ++i) {
            workers.emplace_back(worker);
        }

        // Wait for shutdown signal
        std::cout << "Press Enter to shutdown...\n";
        std::cin.get();
        running = false;

        // Close server socket to unblock accept calls
        server.~Socket();

        // Join all threads
        for (auto& t : workers) {
            if (t.joinable()) t.join();
        }

        return 0;
    } 
    catch (const std::exception& e) {
        std::cerr << "Server fatal error: " << e.what() << "\n";
        return 1;
    }
}