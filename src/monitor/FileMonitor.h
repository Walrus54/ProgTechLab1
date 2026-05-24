#pragma once

#include <atomic>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include <QObject>

#include "checkers/IFileChecker.h"
#include "core/FileTypes.h"
#include "logging/ILogger.h"

/// @brief Монитор наблюдаемых файлов
class FileMonitor : public QObject {
    Q_OBJECT

public:
    /// @brief Конструктор
    /// @param[in] pollIntervalMs Период опроса файлов в миллисекундах
    /// @param[in] checker Реализация проверки файлов (передаётся во владение)
    /// @param[in] logger Логгер
    FileMonitor(int pollIntervalMs, std::unique_ptr<IFileChecker> checker, const std::shared_ptr<ILogger>& logger);

    /// @brief Деструктор
    ~FileMonitor() override;

    /// @brief Добавить файл под наблюдение
    /// @param[in] path Путь к файлу
    /// @return false, если файл уже наблюдается
    bool addFile(const std::string& path);

    /// @brief Снять файл с наблюдения
    /// @param[in] path Путь к файлу
    /// @return false, если файл не наблюдался
    bool removeFile(const std::string& path);

    /// @brief Получить снимок наблюдаемых файлов и их состояния
    /// @return Список файлов с признаком существования и размером
    const std::vector<FileInfo> watchedFiles() const;

    /// @brief Запустить поток опроса
    void start();

    /// @brief Остановить поток опроса и дождаться его завершения
    void stop();

signals:
    /// @brief Файл был изменён
    /// @param[out] event Описание произошедшего изменения
    void fileEvent(const FileInfo& event);

private:
    /// @brief Тело рабочего потока: цикл опроса
    void run();

    /// @brief Один проход по всем файлам
    void checkFiles();

    std::vector<std::string> files_;                    ///< Наблюдаемые пути
    std::unordered_map<std::string, FileInfo> states_;  ///< Состояние по путям
    std::unique_ptr<IFileChecker> checker_;             ///< Проверка через интерфейс
    std::shared_ptr<ILogger> logger_;                   ///< Логгер
    std::thread worker_;                                ///< Поток опроса
    std::atomic<bool> running_;                         ///< Признак работы потока опроса
    mutable std::mutex mutex_;                          ///< Защищает files_ и states_
    int pollIntervalMs_;                                ///< Период опроса в миллисекундах
};
