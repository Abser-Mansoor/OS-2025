#include "socket.hpp"
#include "connection_handler.hpp"

ConnectionHandler::ConnectionHandler(MessageQueue& queue) : queue_(queue) {}
void ConnectionHandler::handle(int client_fd) {
    try {
        // Creates client socket
        os_socket::Socket client_socket(client_fd);
        // Timeout to prevent hanging 
        client_socket.setReceiveTimeout(5);

        char buffer[1024] = {0};
        ssize_t bytes_read = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

        if (bytes_read <= 0) {
            if (bytes_read == 0) {
                std::cerr << "Client disconnected\n";
            } else {
                std::cerr << "Receive error: " << strerror(errno) << "\n";
            }
            return;
        }

        buffer[bytes_read] = '\0';
        queue_.push(client_fd, std::string(buffer)); // Producer: Adds message to queue
    } 
    catch (const std::exception& e) {
        std::cerr << "Connection handling error: " << e.what() << "\n";
    }
}