#pragma once

#include <memory>

#include "logging/ILogger.h"

/// @brief Получить единственный экземпляр журнала
/// @return Разделяемый указатель на единственный экземпляр ILogger
std::shared_ptr<ILogger> logger();
