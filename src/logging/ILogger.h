#pragma once

#include <string>

/// @brief Интерфейс журнала
class ILogger {
public:
    /// @brief Деструктор по умолчанию
    virtual ~ILogger() = default;

    /// @brief Перенаправить журнал в файл
    /// @param[in] path Путь к файлу журнала; пустой путь — вывод в stderr
    virtual void setOutputFile(const std::string& path) = 0;

    /// @brief Записать сообщение
    /// @param[in] msg Текст сообщения
    virtual void log(const std::string& msg) = 0;
};
