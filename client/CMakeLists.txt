cmake_minimum_required(VERSION 2.8)
project(sdl)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
add_library(sdldemo
  src/area.cpp
  src/sdltexture.cpp
  src/sdlexception.cpp
  src/sdlwindow.cpp
  src/anglemanager.cpp
)
include_directories(${PROJECT_BINARY_DIR})
add_executable (sdl-static
  src/mainstatic.cpp  
)
target_link_libraries(sdl-static sdldemo SDL2 SDL2_image SDL2_mixer pthread)
add_executable (raycastingtest
  src/mainraycasting.cpp  
)
target_link_libraries(raycastingtest sdldemo SDL2 SDL2_image SDL2_mixer pthread)
