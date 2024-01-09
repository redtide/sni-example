set(PROJECT_SOURCES
    sni/dbustypes.h
    sni/dbustypes.cpp
    sni/statusnotifieritem.h
    sni/statusnotifieritem.cpp
    sni/org.kde.StatusNotifierItem.xml
    sni-example.hpp
    sni-example.cpp
)
source_group("" FILES ${PROJECT_SOURCES})

qt_add_dbus_adaptor(PROJECT_SOURCES
    sni/org.kde.StatusNotifierItem.xml
    sni/statusnotifieritem.h
    StatusNotifierItem
)
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION ${PROJECT_SOURCES})
else()
    add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
   "${CMAKE_CURRENT_BINARY_DIR}"
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Widgets
    Qt::DBus
    dbusmenu-qt${QT_VERSION_MAJOR}
)
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()