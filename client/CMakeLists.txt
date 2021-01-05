cmake_minimum_required(VERSION 2.8)
project(sdl)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -pthread")
add_library(sdldemo
  src/area.cpp
  src/audio.cpp
  src/hud.cpp
  src/sdltexture.cpp
  src/sdlanimation.cpp
  src/sdlexception.cpp
  src/sdlwindow.cpp
  src/player.cpp
  src/raycaster.cpp
  src/drawable.cpp
  src/audiomanager.cpp
  src/texturemanager.cpp
  src/commandsender.cpp
  src/commandexecuter.cpp
  ../common/src/Map/Map.cpp
  ../common/src/Socket/SocketCommunication.cpp
  ../common/src/Socket/SocketWrapper.cpp
  ../common/src/Thread/Thread.cpp
  ../common/src/Map/Map.cpp

)
include_directories(${PROJECT_BINARY_DIR})
add_executable (sdl-wall
  src/mainwall.cpp
)
#add_executable (raycastinglord
#  src/raycastingLord.cpp
#)
target_link_libraries(sdl-wall sdldemo SDL2 SDL2_image SDL2_mixer SDL2_ttf)
#target_link_libraries(raycastinglord sdldemo SDL2 SDL2_image SDL2_mixer)
