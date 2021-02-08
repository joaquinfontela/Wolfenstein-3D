cmake_minimum_required(VERSION 3.5)

project(editor LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lyaml-cpp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L/usr/local/lib -I/usr/local/include -std=c++11 -pthread -g")

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        editor.cpp
        editor.ui
        decoration_tile_factory.cpp
        door_tile_factory.cpp
        item_tile_factory.cpp
        map_canvas.cpp
        map_actions.cpp
        PathFactory.cpp
        size_window.cpp
        tile_container_actions.cpp
        tiles_container.cpp
        YAMLConversor.cpp
        wall_tile_factory.cpp
        ../../common/src/YAML/YAMLMapWriter.cpp
        ../../common/src/YAML/YAMLMapReader.cpp
        ../../common/src/Coordinate/Coordinate.cpp
        map_painter.cpp
        map_save.cpp
        open_window.cpp
        save_window.cpp
        map_scene.cpp
        tile_item.cpp
        fake_wall_tile_factory.cpp
        tile_factory.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(editor
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(editor SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(editor
            ${PROJECT_SOURCES}
        )
    endif()
endif()

find_package(PkgConfig)
pkg_check_modules(YAMLCPP REQUIRED yaml-cpp>=0.5)

target_link_libraries(editor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${YAMLCPP_LIBRARIES})
