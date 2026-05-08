#pragma once

#include <cstdint>
#include <string>

/// @brief Универсальная запись о наблюдаемом файле (снимок состояния и событие)
struct FileInfo {
    std::string path;         ///< Путь к файлу
    bool seen = false;        ///< Была ли уже хотя бы одна проверка этого файла
    bool exists = false;      ///< Существует ли файл на момент снимка
    std::uintmax_t size = 0;  ///< Размер в байтах (актуален при exists == true)
    std::string description;  ///< Описание события (заполняется чекером)
};
