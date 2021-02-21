#include "luasender.h"
#include "lua.hpp"
#include "lualib.h"

#include <thread>
#include <chrono>
#include <SDL2/SDL.h>
#include "../../../common/includes/protocol.h"




static int wrap_playerInSight(lua_State* luaState){

  Lua::GameState* gameState = static_cast<Lua::GameState*>(lua_touserdata(luaState, 1));

  int returnValue = gameState->playerInSight();
  lua_pushnumber(luaState, returnValue);
  return 1;
}

static int wrap_facingWall(lua_State* luaState){

  Lua::GameState* gameState = static_cast<Lua::GameState*>(lua_touserdata(luaState, 1));

  int returnValue = gameState->facingWall();
  lua_pushnumber(luaState, returnValue);
  return 1;
}

void LuaSender::checkForQuit(){
  while(getchar() != 'q'){

  }
  alive = false;
}

void updateKeyState(KeyState& ks, int keyPressed){

  switch(keyPressed){

    case 100:
    ks.A = 1;
    break;
    case 500:
    ks.A = 0;
    break;
    case 200:
    ks.D = 1;
    break;
    case 600:
    ks.D = 0;
    break;
    case 300:
    ks.W = 1;
    break;
    case 700:
    ks.W = 0;
    break;
    case 400:
    ks.S = 1;
    break;
    case 800:
    ks.S = 0;
    break;
  }
}

void LuaSender::stopPlayer(KeyState& ks){
  if(ks.A == 1){
    this->update(500);
    updateKeyState(ks, 500);
  }

  if(ks.S == 1){
    this->update(800);
    updateKeyState(ks, 800);
  }

  if(ks.D == 1){
    this->update(600);
    updateKeyState(ks, 600);
  }

  if(ks.W == 1){
    this->update(700);
    updateKeyState(ks, 700);
  }
}

void LuaSender::run(){

  std::thread quitThread(&LuaSender::checkForQuit, this);

  lua_State* luaState;
  luaState = luaL_newstate();
  luaL_openlibs(luaState);
  this->update(19);

  if(luaL_loadfile(luaState, scriptName.c_str()) != LUA_OK){
    std::cout<<"Failure to open Lua Script"<<std::endl;
  }

  if (lua_pcall(luaState, 0, LUA_MULTRET, 0)) {
    std::cerr << "Something went wrong during execution" << std::endl;
    std::cerr << lua_tostring(luaState, -1) << std::endl;
    lua_pop(luaState,1);
  }

  lua_register(luaState, "facingWall", wrap_facingWall);
  lua_register(luaState, "playerInSight", wrap_playerInSight);

  // Llamado a la funcion que, por el momento, devuelve un input random para mandar al server.
  KeyState keyState;
  keyState.W = 0;
  keyState.S = 0;
  keyState.A = 0;
  keyState.D = 0;

  while(alive){

    std::cout<<"KeyState: A: "<<keyState.A<<", S: "<<keyState.S<<", D: "<<keyState.D<<", W: "<<keyState.W<<std::endl;
    this->stopPlayer(keyState);
    lua_getglobal(luaState, "getInput");
    lua_pushlightuserdata(luaState, this->gameState);
    // Esto no esta funcionando por ahora, el objetivo seria pasarle un struct/objeto que represente el estado del juego y que lua tome su decision.
    if(lua_pcall(luaState, 1, 1, 0)){
      std::cout<<"Fallo llamando a lua: "<<lua_tostring(luaState, -1)<<std::endl;
      lua_pop(luaState, 1);
      break;
    }

    int n = lua_tonumber(luaState, -1);
    this->update(n);
    updateKeyState(keyState, n);
    lua_pop(luaState, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(700));

  }
  quitThread.join();
  lua_close(luaState);
}
