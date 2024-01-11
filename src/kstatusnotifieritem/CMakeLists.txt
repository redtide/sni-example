cmake_minimum_required(VERSION 3.15)
project(kstatusnotifieritem
    VERSION 5.248.0 # reference from which version the code was taken
    LANGUAGES CXX
)
add_library(${PROJECT_NAME})
add_library(kde::statusnotifieritem ALIAS ${PROJECT_NAME})

set(KSNI_DBUS_SOURCES)
qt_add_dbus_adaptor(KSNI_DBUS_SOURCES
    org.kde.StatusNotifierItem.xml
    kstatusnotifieritemdbus_p.h
    KStatusNotifierItemDBus
)
set(KSNI_WATCHER_XML org.kde.StatusNotifierWatcher.xml)
qt_add_dbus_interface(KSNI_DBUS_SOURCES
    ${KSNI_WATCHER_XML}
    statusnotifierwatcher_interface
)
set(KSNI_NOTIFICATIONS_XML org.freedesktop.Notifications.xml)
qt_add_dbus_interface(KSNI_DBUS_SOURCES
    ${KSNI_NOTIFICATIONS_XML}
    notifications_interface
)
set(KSNI_SOURCES
    ${KSNI_DBUS_SOURCES}
    kstatusnotifieritem.h
    kstatusnotifieritem.cpp
    kstatusnotifieritemdbus_p.h
    kstatusnotifieritemdbus_p.cpp
    kstatusnotifieritemprivate_p.h
    org.kde.StatusNotifierItem.xml
    ${KSNI_NOTIFICATIONS_XML}
    ${KSNI_WATCHER_XML}
)
source_group("" FILES ${KSNI_SOURCES})
target_sources(${PROJECT_NAME} PRIVATE ${KSNI_SOURCES})

configure_file(config-kstatusnotifieritem.h.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/config-kstatusnotifieritem.h
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Widgets
    Qt::DBus
)
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6 AND SNI_USE_LIBDBUSMENU_LXQT AND NOT SNI_USE_KSNI)
    target_link_libraries(${PROJECT_NAME} PUBLIC dbusmenu-lxqt)
else()
    target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src)
    target_link_libraries(${PROJECT_NAME}      PUBLIC qt::dbusmenu)
endif()
