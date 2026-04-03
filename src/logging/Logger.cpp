#include "logging/Logger.h"

#include <iostream>

Logger::~Logger() {
    if (file_.is_open()) {
        file_.close();
    }
}

void Logger::setOutputFile(const std::string& path) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (path.empty()) {
        return;
    }
    file_.open(path, std::ios::out | std::ios::app);
}

void Logger::log(const std::string& msg) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (file_.is_open()) {
        file_ << msg << '\n';
        file_.flush();
    } else {
        std::cerr << msg << '\n';
    }
}
