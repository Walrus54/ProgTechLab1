#pragma once

#include <memory>

#include <QObject>

#include "core/FileTypes.h"
#include "logging/ILogger.h"
#include "notifier/INotifier.h"

/// @brief Приёмник событий, пишущий их в журнал
class EventNotifier : public QObject, public INotifier {
    Q_OBJECT

public:
    /// @brief Конструктор
    /// @param[in] logger Логгер
    explicit EventNotifier(const std::shared_ptr<ILogger>& logger);

    /// @brief Записать событие в журнал
    /// @param[in] event Описание произошедшего изменения
    void notify(const FileInfo& event) override;

public slots:
    /// @brief Слот, подключаемый к сигналу FileMonitor::fileEvent
    /// @param[in] event Описание произошедшего изменения
    void onFileEvent(const FileInfo& event);

private:
    std::shared_ptr<ILogger> logger_;  ///< Логгер
};
