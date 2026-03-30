cmake_minimum_required(VERSION 3.16)

project(file_watcher
    VERSION 1.0.0
    DESCRIPTION "Console file-watching utility (existence + size)"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Qt meta-object compiler runs automatically for Q_OBJECT headers.
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Threads REQUIRED)

# Общие флаги предупреждений для всех модулей (директория-скоуп).
add_compile_options(-Wall -Wextra -Wpedantic)

# Каждый модуль собирается отдельной библиотекой в src/<module>/CMakeLists.txt.
add_subdirectory(src)
