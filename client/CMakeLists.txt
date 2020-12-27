cmake_minimum_required(VERSION 2.8)
project(sdl)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -pthread")
add_library(sdldemo
  src/area.cpp
  src/sdltexture.cpp
  src/sdlexception.cpp
  src/sdlwindow.cpp
  src/player.cpp
  src/drawable.cpp
  src/anglemanager.cpp
  src/raycaster.cpp
  src/texturemanager.cpp
  src/commandsender.cpp
  src/commandexecuter.cpp
  ../common/src/Map/Map.cpp
  ../common/src/Socket/SocketCommunication.cpp
  ../common/src/Thread/Thread.cpp
  ../common/src/Map/Map.cpp

)
include_directories(${PROJECT_BINARY_DIR})
add_executable (sdl-wall
  src/mainwall.cpp  
)
add_executable (raycastingtest
  src/mainraycasting.cpp  
)

add_executable (raycastinglord
  src/raycastingLord.cpp  
)
target_link_libraries(sdl-wall sdldemo SDL2 SDL2_image SDL2_mixer)
target_link_libraries(raycastingtest sdldemo SDL2 SDL2_image SDL2_mixer)
target_link_libraries(raycastinglord sdldemo SDL2 SDL2_image SDL2_mixer)
