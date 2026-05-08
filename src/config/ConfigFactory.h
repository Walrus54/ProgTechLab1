#pragma once

#include <memory>

#include "config/IConfig.h"

/// @brief Получить единственный экземпляр конфигурации
/// @return Разделяемый указатель на единственный экземпляр IConfig
std::shared_ptr<IConfig> config();
