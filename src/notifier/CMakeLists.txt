# notifier — приёмник событий. EventNotifier является QObject (слот), поэтому Qt5::Core.
add_library(fw_notifier STATIC
    EventNotifier.cpp
)
target_include_directories(fw_notifier PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(fw_notifier PUBLIC fw_core fw_logging Qt5::Core)
