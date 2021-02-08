cmake_minimum_required(VERSION 3.5)

project(Login LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        login.cpp
        login.h
        login.ui
        create_window.cpp
        create_window.h
        create_window.ui
        join_window.cpp
        join_window.h
        join_window.ui
        match_id.cpp
        match_id.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Login
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Login SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Login
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Login PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
