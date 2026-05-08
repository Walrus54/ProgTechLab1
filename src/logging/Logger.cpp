#include "logging/Logger.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace {

/// @brief Текущее локальное время в формате "yyyy-MM-dd HH:mm:ss".
/// @return Строка с датой и временем.
std::string timestamp() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
#if defined(_WIN32)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ostringstream out;
    out << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return out.str();
}

}  // namespace

Logger::~Logger() {
    if (file_.is_open()) {
        file_.close();
    }
}

void Logger::setOutputFile(const std::string& path) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (file_.is_open()) {
        file_.close();
    }
    if (path.empty()) {
        return;
    }
    file_.open(path, std::ios::out | std::ios::app);
}

void Logger::log(const std::string& msg) {
    const std::string line = "[" + timestamp() + "] " + msg;

    std::lock_guard<std::mutex> lock(mutex_);
    if (file_.is_open()) {
        file_ << line << '\n';
        file_.flush();
    } else {
        std::cerr << line << '\n';
    }
}
