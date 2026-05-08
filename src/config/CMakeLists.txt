# config — конфигурация и её фабрика-синглтон. Логирует через fw_logging.
add_library(fw_config STATIC
    Config.cpp
    ConfigFactory.cpp
)
target_include_directories(fw_config PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(fw_config PUBLIC fw_logging)
