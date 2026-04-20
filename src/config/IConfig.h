#pragma once

#include <string>

/// @brief Интерфейс конфигурации
class IConfig {
public:
    /// @brief Деструктор по умолчанию
    virtual ~IConfig() = default;

    /// @brief Получить строковое значение по ключу
    /// @param[in] key Имя ключа
    /// @param[in] defaultValue Значение по умолчанию, если ключа нет
    /// @return Значение ключа или defaultValue
    virtual std::string get(const std::string& key,
                            const std::string& defaultValue = std::string()) const = 0;

    /// @brief Получить целочисленное значение по ключу
    /// @param[in] key Имя ключа
    /// @param[in] defaultValue Значение по умолчанию при отсутствии ключа или ошибке разбора
    /// @return Значение ключа или defaultValue
    virtual int getInt(const std::string& key, int defaultValue = 0) const = 0;
};
