#pragma once

#include "core/FileTypes.h"

/// @brief Интерфейс приёмника событий об изменении файлов
class INotifier {
public:
    /// @brief Деструктор по умолчанию
    virtual ~INotifier() = default;

    /// @brief Обработать событие изменения файла
    /// @param[in] event Описание произошедшего изменения
    virtual void notify(const FileInfo& event) = 0;
};
