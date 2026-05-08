#pragma once

#include <fstream>
#include <mutex>
#include <string>

#include "logging/ILogger.h"

/// @brief Потокобезопасная реализация журнала
class Logger : public ILogger {
public:
    /// @brief Конструктор по умолчанию
    Logger() = default;

    /// @brief Деструктор
    ~Logger() override;

    /// @brief Перенаправить журнал в файл
    /// @param[in] path Путь к файлу журнала; пустой путь — вывод в stderr
    void setOutputFile(const std::string& path) override;

    /// @brief Записать сообщение в журнал
    /// @param[in] msg Текст сообщения
    void log(const std::string& msg) override;

private:
    std::ofstream file_;  ///< Файл журнала
    std::mutex mutex_;    ///< Сериализует запись из разных потоков
};
