#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

#include "config/IConfig.h"
#include "logging/ILogger.h"

/// @brief Реализация конфигурации на основе текстового файла
class Config : public IConfig {
public:
    /// @brief Конструктор
    /// @param[in] path Путь к текстовому файлу настроек
    /// @param[in] logger Логгер
    Config(const std::string& path, const std::shared_ptr<ILogger>& logger);

    /// @brief Получить строковое значение по ключу
    /// @param[in] key Имя ключа
    /// @param[in] defaultValue Значение по умолчанию, если ключа нет
    /// @return Значение ключа или defaultValue
    std::string get(const std::string& key,
                    const std::string& defaultValue = std::string()) const override;

    /// @brief Получить целочисленное значение по ключу
    /// @param[in] key Имя ключа
    /// @param[in] defaultValue Значение по умолчанию при отсутствии ключа или ошибке разбора
    /// @return Значение ключа или defaultValue
    int getInt(const std::string& key, int defaultValue = 0) const override;

private:
    std::unordered_map<std::string, std::string> data_;  ///< Пары ключ-значение
    std::shared_ptr<ILogger> logger_;                    ///< Логгер
    mutable std::mutex mutex_;                           ///< Защищает data_
};
