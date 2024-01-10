cmake_minimum_required(VERSION 3.15)
project(dbusmenu-qt
    VERSION 0.1.0
    LANGUAGES CXX
)
set(PROJECT_QT_VERSION 5 CACHE STRING "Qt version to use [default: 5]")

set(CMAKE_AUTOMOC ON)
find_package(QT NAMES Qt${PROJECT_QT_VERSION})
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS DBus Widgets)

qt_add_dbus_adaptor(DBUSMENU_EXPORTER_SOURCES
    com.canonical.dbusmenu.xml
    dbusmenuexporterdbus_p.h
    DBusMenuExporterDBus
)
list(APPEND DBUSMENU_SOURCES
    ${DBUSMENU_EXPORTER_SOURCES}
    dbusmenuexporter.cpp
    dbusmenuexporterdbus_p.cpp
    dbusmenu_p.cpp
    dbusmenushortcut_p.cpp
    dbusmenutypes_p.cpp
    utils.cpp
    dbusmenuexporterdbus_p.h
    dbusmenuexporter.h
    dbusmenuexporterprivate_p.h
    dbusmenu_p.h
    dbusmenushortcut_p.h
    dbusmenutypes_p.h
    debug_p.h
    utils_p.h
)
add_library(${PROJECT_NAME} STATIC ${DBUSMENU_SOURCES})
add_library(qt::dbusmenu ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Widgets
    Qt::DBus
)
