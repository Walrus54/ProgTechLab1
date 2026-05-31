#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <QObject>

#include "checkers/FileChecker.h"
#include "config/ConfigFactory.h"
#include "logging/LoggerFactory.h"
#include "monitor/FileMonitor.h"
#include "notifier/EventNotifier.h"

namespace {

/// @brief Обрезать ведущие и завершающие пробельные символы.
/// @param[in] s Исходная строка.
/// @return Строка без обрамляющих пробелов (или пустая, если все символы пробельные).
std::string trim(const std::string& s) {
    const auto begin = s.find_first_not_of(" \t");
    if (begin == std::string::npos) {
        return std::string();
    }
    const auto end = s.find_last_not_of(" \t");
    return s.substr(begin, end - begin + 1);
}

}  // namespace

/// @brief Точка входа в программу.
/// @param[in] argc Количество аргументов командной строки.
/// @param[in] argv Массив аргументов командной строки.
/// @return Код завершения процесса.
int main(int argc, char* argv[]) {
    const std::shared_ptr<IConfig> cfg = config();

    const std::string logFile = cfg->get("log_file");
    if (logFile.empty()) {
        logger()->log("Config error: 'log_file' is not set");
        return 1;
    }
    const std::string pollInterval = cfg->get("poll_interval_ms");
    if (pollInterval.empty()) {
        logger()->log("Config error: 'poll_interval_ms' is not set");
        return 1;
    }

    logger()->setOutputFile(logFile);

    auto checker = std::make_unique<FileChecker>();
    FileMonitor monitor(cfg->getInt("poll_interval_ms"), std::move(checker), logger());

    EventNotifier notifier(logger());

    QObject::connect(&monitor, &FileMonitor::fileEvent, &notifier,
                     &EventNotifier::onFileEvent, Qt::DirectConnection);

    for (int i = 1; i < argc; ++i) {
        const std::string path = argv[i];
        if (monitor.addFile(path)) {
            logger()->log("Added: " + path);
        }
    }

    logger()->log("file_watcher started. Commands: add <path>, remove <path>, list, quit.");
    monitor.start();

    std::string raw;
    while (true) {
        if (!std::getline(std::cin, raw)) {
            break;
        }
        const std::string line = trim(raw);
        if (line.empty()) {
            continue;
        }

        const auto sp = line.find(' ');
        const std::string cmd = (sp == std::string::npos) ? line : line.substr(0, sp);
        const std::string arg =
            (sp == std::string::npos) ? std::string() : trim(line.substr(sp + 1));

        if (cmd == "quit" || cmd == "exit") {
            break;
        } else if (cmd == "list") {
            const std::vector<FileInfo> files = monitor.watchedFiles();
            if (files.empty()) {
                logger()->log("No files are being watched");
            } else {
                logger()->log("Watched files:");
                for (const FileInfo& f : files) {
                    if (f.exists) {
                        logger()->log("  " + f.path + " - exists, " + std::to_string(f.size) +
                                      " bytes");
                    } else {
                        logger()->log("  " + f.path + " - does not exist");
                    }
                }
            }
        } else if (cmd == "add") {
            if (arg.empty()) {
                logger()->log("Usage: add <path>");
            } else if (monitor.addFile(arg)) {
                logger()->log("Added: " + arg);
            } else {
                logger()->log("Already watched: " + arg);
            }
        } else if (cmd == "remove") {
            if (arg.empty()) {
                logger()->log("Usage: remove <path>");
            } else if (monitor.removeFile(arg)) {
                logger()->log("Removed: " + arg);
            } else {
                logger()->log("Not watched: " + arg);
            }
        } else {
            logger()->log("Unknown command: " + cmd);
        }
    }

    monitor.stop();
    return 0;
}
