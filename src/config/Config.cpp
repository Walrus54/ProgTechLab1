#include "config/Config.h"

#include <fstream>
#include <string>

namespace {

/// @brief Обрезать ведущие и завершающие пробельные символы.
/// @param[in] s Исходная строка.
/// @return Строка без обрамляющих пробелов.
std::string trim(const std::string& s) {
    const auto begin = s.find_first_not_of(" \t\r\n");
    if (begin == std::string::npos) {
        return std::string();
    }
    const auto end = s.find_last_not_of(" \t\r\n");
    return s.substr(begin, end - begin + 1);
}

}  // namespace

Config::Config(const std::string& path, const std::shared_ptr<ILogger>& logger)
    : logger_(logger) {
    std::ifstream file(path);
    if (!file.is_open()) {
        logger_->log("Config: cannot open " + path);
        return;
    }

    std::string raw;
    while (std::getline(file, raw)) {
        const std::string line = trim(raw);
        if (line.empty() || line.front() == '#' || line.front() == ';') {
            continue;
        }
        const auto eq = line.find('=');
        if (eq == std::string::npos || eq == 0) {
            continue;
        }
        const std::string key = trim(line.substr(0, eq));
        const std::string value = trim(line.substr(eq + 1));
        data_[key] = value;
    }

    logger_->log("Config: loaded from " + path);
}

std::string Config::get(const std::string& key, const std::string& defaultValue) const {
    std::lock_guard<std::mutex> lock(mutex_);
    const auto it = data_.find(key);
    return it != data_.end() ? it->second : defaultValue;
}

int Config::getInt(const std::string& key, int defaultValue) const {
    std::lock_guard<std::mutex> lock(mutex_);
    const auto it = data_.find(key);
    if (it == data_.end()) {
        return defaultValue;
    }
    try {
        size_t pos = 0;
        const int value = std::stoi(it->second, &pos);
        return pos == it->second.size() ? value : defaultValue;
    } catch (const std::exception&) {
        return defaultValue;
    }
}
