#include "monitor/FileMonitor.h"

#include <chrono>
#include <filesystem>
#include <memory>
#include <optional>
#include <system_error>
#include <utility>
#include <vector>

namespace fs = std::filesystem;

FileMonitor::FileMonitor(int pollIntervalMs, std::unique_ptr<IFileChecker> checker, const std::shared_ptr<ILogger>& logger)
    : checker_(std::move(checker)),
      logger_(logger),
      running_(false),
      pollIntervalMs_(pollIntervalMs > 0 ? pollIntervalMs : 1) {}

FileMonitor::~FileMonitor() {
    stop();
}

bool FileMonitor::addFile(const std::string& path) {
    for (std::size_t i = 0; i < files_.size(); ++i) {
        if (files_[i] == path) {
            logger_->log("File already watched: " + path);
            return false;
        }
    }
    files_.push_back(path);
    logger_->log("File added: " + path);
    return true;
}

bool FileMonitor::removeFile(const std::string& path) {
    for (std::size_t i = 0; i < files_.size(); ++i) {
        if (files_[i] == path) {
            files_.erase(files_.begin() + i);
            states_.erase(path);
            logger_->log("File removed: " + path);
            return true;
        }
    }
    logger_->log("File not watched: " + path);
    return false;
}

const std::vector<FileInfo> FileMonitor::watchedFiles() const {
    std::vector<FileInfo> result;
    result.reserve(files_.size());
    for (const std::string& path : files_) {
        std::error_code ec;
        const std::uintmax_t size = fs::file_size(path, ec);

        FileInfo info;
        info.path = path;
        info.exists = !ec;
        info.size = !ec ? size : 0;
        result.push_back(info);
    }
    return result;
}

void FileMonitor::start() {
    if (running_.exchange(true)) {
        logger_->log("Monitor already running");
        return;
    }
    worker_ = std::thread(&FileMonitor::run, this);
    logger_->log("Monitor started");
}

void FileMonitor::stop() {
    if (!running_.exchange(false)) {
        logger_->log("Monitor already stopped");
        return;
    }
    if (worker_.joinable()) {
        worker_.join();
    }
    logger_->log("Monitor stopped");
}

void FileMonitor::run() {
    while (running_.load()) {
        checkFiles();
        std::this_thread::sleep_for(std::chrono::milliseconds(pollIntervalMs_));
    }
}

void FileMonitor::checkFiles() {
    for (const std::string& path : files_) {
        std::error_code ec;
        const std::uintmax_t size = fs::file_size(path, ec);

        FileInfo curr;
        curr.path = path;
        curr.seen = true;
        curr.exists = !ec;
        curr.size = curr.exists ? size : 0;

        FileInfo prev;
        auto it = states_.find(path);
        if (it != states_.end()) {
            prev = it->second;
        }

        if (std::optional<FileInfo> event = checker_->check(prev, curr)) {
            emit fileEvent(*event);
        }
        states_[path] = curr;
    }
}
