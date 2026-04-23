#include "config/ConfigFactory.h"

#include "config/Config.h"
#include "logging/LoggerFactory.h"

std::shared_ptr<IConfig> config() {
    static std::shared_ptr<IConfig> instance;
    if (instance == nullptr) {
        instance = std::make_shared<Config>("config.txt", logger());
    }
    return instance;
}
