# logging — журнал и его фабрика-синглтон. Зависит только от стандартной библиотеки.
add_library(fw_logging STATIC
    Logger.cpp
    LoggerFactory.cpp
)
target_include_directories(fw_logging PUBLIC ${PROJECT_SOURCE_DIR}/src)
