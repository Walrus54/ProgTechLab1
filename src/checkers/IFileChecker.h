#pragma once

#include <optional>
#include <string>

#include "core/FileTypes.h"

/// @brief Интерфейс проверки файла
class IFileChecker {
public:
    /// @brief Деструктор по умолчанию
    virtual ~IFileChecker() = default;

    /// @brief Проверить файл по двум соседним снимкам
    /// @param[in] prev Предыдущий снимок
    /// @param[in] curr Текущий снимок
    /// @return Событие, если отслеживаемое свойство изменилось, иначе std::nullopt
    virtual std::optional<FileInfo> check(const FileInfo& prev, const FileInfo& curr) const = 0;

    /// @brief Копирование запрещено
    IFileChecker(const IFileChecker&) = delete;
    /// @brief Присваивание запрещено
    IFileChecker& operator=(const IFileChecker&) = delete;

protected:
    /// @brief Конструктор по умолчанию
    IFileChecker() = default;
};
