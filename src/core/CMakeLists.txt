# core — только заголовки (FileInfo): интерфейсная библиотека.
add_library(fw_core INTERFACE)
target_include_directories(fw_core INTERFACE ${PROJECT_SOURCE_DIR}/src)
