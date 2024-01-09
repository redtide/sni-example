cmake_minimum_required(VERSION 3.5)
project(sni-example
    VERSION 0.1.0
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(PROJECT_QT_VERSION 5 CACHE STRING "Qt version to use                      [default: 5]")
option(SNI_USE_LIBDBUSMENU_LXQT       "Use the LXQt version of libdbusmenu-qt [default: OFF]" OFF)

set(CMAKE_AUTOMOC ON)
find_package(QT NAMES Qt${PROJECT_QT_VERSION})
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS DBus Widgets)

add_subdirectory(src)
