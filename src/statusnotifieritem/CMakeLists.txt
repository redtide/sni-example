cmake_minimum_required(VERSION 3.15)
project(statusnotifieritem
    VERSION 0.1.0
    LANGUAGES CXX
)
add_library(${PROJECT_NAME})
add_library(qt::statusnotifieritem ALIAS ${PROJECT_NAME})

qt_add_dbus_adaptor(SNI_DBUS_SOURCES
    org.kde.StatusNotifierItem.xml
    statusnotifieritem.h
    StatusNotifierItem
)
set(SNI_SOURCES
    ${SNI_DBUS_SOURCES}
    dbustypes.h
    dbustypes.cpp
    statusnotifieritem.h
    statusnotifieritem.cpp
    org.kde.StatusNotifierItem.xml
)
source_group("" FILES ${SNI_SOURCES})
target_sources(${PROJECT_NAME} PRIVATE ${SNI_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Widgets
    Qt::DBus
)
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6 AND SNI_USE_LIBDBUSMENU_LXQT)
    target_link_libraries(${PROJECT_NAME} PUBLIC dbusmenu-lxqt)
else()
    target_link_libraries(${PROJECT_NAME}      PUBLIC qt::dbusmenu)
    target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/libdbusmenu-qt)
endif()
