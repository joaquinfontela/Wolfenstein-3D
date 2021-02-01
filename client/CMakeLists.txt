cmake_minimum_required(VERSION 2.8)
project(sdl)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -pthread -O3 -finline-functions -funroll-loops")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lyaml-cpp")

SET(_POSSIBLE_LUA_INCLUDE include include/lua)
SET(_POSSIBLE_LUA_EXECUTABLE lua)
SET(_POSSIBLE_LUA_LIBRARY lua)

# Determine possible naming suffixes (there is no standard for this)
IF(Lua_FIND_VERSION_MAJOR AND Lua_FIND_VERSION_MINOR)
  SET(_POSSIBLE_SUFFIXES "${Lua_FIND_VERSION_MAJOR}${Lua_FIND_VERSION_MINOR}" "${Lua_FIND_VERSION_MAJOR}.${Lua_FIND_VERSION_MINOR}" "-${Lua_FIND_VERSION_MAJOR}.${Lua_FIND_VERSION_MINOR}")
ELSE(Lua_FIND_VERSION_MAJOR AND Lua_FIND_VERSION_MINOR)
  SET(_POSSIBLE_SUFFIXES "52" "5.2" "-5.2" "51" "5.1" "-5.1")
ENDIF(Lua_FIND_VERSION_MAJOR AND Lua_FIND_VERSION_MINOR)

# Set up possible search names and locations
FOREACH(_SUFFIX ${_POSSIBLE_SUFFIXES})
  LIST(APPEND _POSSIBLE_LUA_INCLUDE "include/lua${_SUFFIX}")
  LIST(APPEND _POSSIBLE_LUA_EXECUTABLE "lua${_SUFFIX}")
  LIST(APPEND _POSSIBLE_LUA_LIBRARY "lua${_SUFFIX}")
ENDFOREACH(_SUFFIX)

# Find the lua executable
FIND_PROGRAM(LUA_EXECUTABLE
  NAMES ${_POSSIBLE_LUA_EXECUTABLE}
)

# Find the lua header
FIND_PATH(LUA_INCLUDE_DIR lua.h
  HINTS
  $ENV{LUA_DIR}
  PATH_SUFFIXES ${_POSSIBLE_LUA_INCLUDE}
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
)

# Find the lua library
FIND_LIBRARY(LUA_LIBRARY
  NAMES ${_POSSIBLE_LUA_LIBRARY}
  HINTS
  $ENV{LUA_DIR}
  PATH_SUFFIXES lib64 lib
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw
  /opt/local
  /opt/csw
  /opt
)

IF(LUA_LIBRARY)
  # include the math library for Unix
  IF(UNIX AND NOT APPLE)
    FIND_LIBRARY(LUA_MATH_LIBRARY m)
    SET( LUA_LIBRARIES "${LUA_LIBRARY};${LUA_MATH_LIBRARY}" CACHE STRING "Lua Libraries")
  # For Windows and Mac, don't need to explicitly include the math library
  ELSE(UNIX AND NOT APPLE)
    SET( LUA_LIBRARIES "${LUA_LIBRARY}" CACHE STRING "Lua Libraries")
  ENDIF(UNIX AND NOT APPLE)
ENDIF(LUA_LIBRARY)

# Determine Lua version
IF(LUA_INCLUDE_DIR AND EXISTS "${LUA_INCLUDE_DIR}/lua.h")
  FILE(STRINGS "${LUA_INCLUDE_DIR}/lua.h" lua_version_str REGEX "^#define[ \t]+LUA_RELEASE[ \t]+\"Lua .+\"")

  STRING(REGEX REPLACE "^#define[ \t]+LUA_RELEASE[ \t]+\"Lua ([^\"]+)\".*" "\\1" LUA_VERSION_STRING "${lua_version_str}")
  UNSET(lua_version_str)
ENDIF()

INCLUDE(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LUA_FOUND to TRUE if
# all listed variables are TRUE
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Lua
                                  REQUIRED_VARS LUA_LIBRARIES LUA_INCLUDE_DIR
                                  VERSION_VAR LUA_VERSION_STRING)

MARK_AS_ADVANCED(LUA_INCLUDE_DIR LUA_LIBRARIES LUA_LIBRARY LUA_MATH_LIBRARY LUA_EXECUTABLE)

add_library(sdldemo
  src/ClientMapLoader.cpp
  src/client.cpp
  src/RaycastedAnimation.cpp
  src/area.cpp
  src/log.cpp
  src/doortimer.cpp
  src/scoreboard.cpp
  src/doortile.cpp
  src/audio.cpp
  src/hud.cpp
  src/door.cpp
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
  ../common/src/YAML/YAMLMapReader.cpp
  ../common/src/Coordinate/Coordinate.cpp
  src/log.cpp
  src/Lua/luasender.cpp
  src/Lua/luaraycaster.cpp
  src/Lua/luaexecuter.cpp
  src/Lua/LuaClient.cpp
  src/Lua/GameState.cpp
)

find_package(PkgConfig)
pkg_check_modules(YAMLCPP REQUIRED yaml-cpp>=0.5)


include_directories(/usr/local/include ${LUA_INCLUDE_DIR})
include_directories(${PROJECT_BINARY_DIR})
add_executable (sdl-wall
  src/mainwall.cpp
)
add_executable (lua
  src/Lua/lua_main.cpp
)
target_link_libraries(sdl-wall sdldemo SDL2 SDL2_image SDL2_mixer SDL2_ttf)

target_link_libraries(sdl-wall ${YAMLCPP_LIBRARIES})
target_link_libraries(sdl-wall ${LUA_LIBRARIES} ${CMAKE_DL_LIBS})

target_link_libraries(lua sdldemo SDL2 SDL2_image SDL2_mixer SDL2_ttf)

target_link_libraries(lua ${YAMLCPP_LIBRARIES})
target_link_libraries(lua ${LUA_LIBRARIES} ${CMAKE_DL_LIBS})
