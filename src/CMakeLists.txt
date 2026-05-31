# Модули утилиты: каждый — отдельная библиотека со своими зависимостями.
# Порядок не важен (CMake разрешает связи по именам таргетов).
add_subdirectory(core)
add_subdirectory(logging)
add_subdirectory(config)
add_subdirectory(checkers)
add_subdirectory(notifier)
add_subdirectory(monitor)

# Точка входа: интерактивный CLI.
add_executable(file_watcher main.cpp)
target_link_libraries(file_watcher PRIVATE
    fw_monitor
    fw_notifier
    fw_config
    Qt5::Core
)
