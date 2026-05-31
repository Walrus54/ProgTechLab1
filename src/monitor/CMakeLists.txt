# monitor — поток опроса. FileMonitor является QObject (сигнал) и использует std::thread.
add_library(fw_monitor STATIC
    FileMonitor.cpp
)
target_include_directories(fw_monitor PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(fw_monitor PUBLIC
    fw_core
    fw_checkers
    fw_logging
    Qt5::Core
    Threads::Threads
)
