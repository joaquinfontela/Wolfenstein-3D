cmake_minimum_required(VERSION 2.8)
project(sdl)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_library(sdldemo
  src/area.cpp
  src/sdltexture.cpp
  src/sdlexception.cpp
  src/sdldrawing.cpp
  src/sdlwindow.cpp
)
include_directories(${PROJECT_BINARY_DIR})
add_executable (sdl-static
  src/mainstatic.cpp  
)
target_link_libraries(sdl-static sdldemo SDL2 SDL2_image)
