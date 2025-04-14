#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <utility>
#include <string>

class MessageQueue {
    std::queue<std::pair<int, std::string>> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;

public:
    void push(int client_fd, const std::string& message);
    std::pair<int, std::string> pop();
    

};