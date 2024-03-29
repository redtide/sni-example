set(PROJECT_SOURCES
    example/example.hpp
    example/example.cpp
    example/volume.hpp
    example/volume.cpp
)
source_group("" FILES ${PROJECT_SOURCES})

# KSNI needs its own libdbusmenu-qt
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6 AND SNI_USE_LIBDBUSMENU_LXQT AND NOT SNI_USE_KSNI)
    find_package(dbusmenu-lxqt REQUIRED)
else()
    add_subdirectory(libdbusmenu-qt)
    set(HAVE_DBUSMENUQT 1)
endif()

if(SNI_USE_KSNI)
    add_subdirectory(kstatusnotifieritem)
else()
    add_subdirectory(statusnotifieritem)
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION ${PROJECT_SOURCES})
else()
    add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Widgets
    Qt::DBus
)
if(SNI_USE_KSNI)
    target_include_directories(${PROJECT_NAME} PRIVATE src/kstatusnotifieritem)
    target_link_libraries(${PROJECT_NAME}      PRIVATE kde::statusnotifieritem)
else()
    target_include_directories(${PROJECT_NAME} PRIVATE src/statusnotifieritem)
    target_link_libraries(${PROJECT_NAME}      PRIVATE qt::statusnotifieritem)
endif()

if(SNI_USE_KSNI)
    target_compile_definitions(${PROJECT_NAME} PRIVATE KSNI=1)
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
