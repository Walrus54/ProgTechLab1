#include "logging/LoggerFactory.h"

#include "logging/Logger.h"

std::shared_ptr<ILogger> logger() {
    static std::shared_ptr<ILogger> instance;
    if (instance == nullptr) {
        instance = std::make_shared<Logger>();
    }
    return instance;
}
