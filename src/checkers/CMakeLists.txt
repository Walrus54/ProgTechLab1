# checkers — интерфейс проверки и единственная реализация. Использует типы из core.
add_library(fw_checkers STATIC
    FileChecker.cpp
)
target_include_directories(fw_checkers PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(fw_checkers PUBLIC fw_core)
