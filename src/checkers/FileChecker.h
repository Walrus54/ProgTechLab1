#pragma once

#include <optional>
#include <string>

#include "checkers/IFileChecker.h"

/// @brief Реализация проверки существования и размера файла
class FileChecker : public IFileChecker {
public:
    /// @brief Проверить файл по двум соседним снимкам
    /// @param[in] prev Предыдущий снимок
    /// @param[in] curr Текущий снимок
    /// @return Событие удаления, появления или изменения размера, иначе std::nullopt
    std::optional<FileInfo> check(const FileInfo& prev, const FileInfo& curr) const override;
};
