#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <utility>

class MessageQueue {
public:
    void push(int client_fd, const std::string& message);
    std::pair<int, std::string> pop();
    
private:
    std::queue<std::pair<int, std::string>> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;
};