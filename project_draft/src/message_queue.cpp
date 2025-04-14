#include "message_queue.hpp"

void MessageQueue::push(int client_fd, const std::string &message) {
    std::unique_lock<std::mutex> lock(mutex_);
    queue_.emplace(client_fd, message);
    cv_.notify_one();
}

std::pair<int, std::string> MessageQueue::pop() {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this] { return !queue_.empty(); });
    auto item = queue_.front();
    queue_.pop();
    return item;
}