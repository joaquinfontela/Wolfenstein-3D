#include "luasender.h"
#include "lua.hpp"
#include "lualib.h"

#include <thread>
#include <chrono>


void LuaSender::run(){

  lua_State* luaState;
  luaState = luaL_newstate();
  luaL_openlibs(luaState);

  if(luaL_loadfile(luaState, "../Lua/script.lua")){
    std::cout<<"Failure to open Lua Script"<<std::endl;
  }

  // Llamado a la funcion que, por el momento, devuelve un input random para mandar al server.

  while(alive){

    lua_getglobal(luaState, "getInput");

    // Esto no esta funcionando por ahora, el objetivo seria pasarle un struct/objeto que represente el estado del juego y que lua tome su decision.
    if(lua_pcall(luaState, 0, 1, 0)){
      std::cout<<"Fallo llamando a lua: "<<lua_tostring(luaState, -1)<<std::endl;
      lua_pop(luaState, 1);
    }

    this->update(lua_tonumber(luaState, -1));
    std::cout<<lua_tonumber(luaState, -1)<<std::endl;
    lua_pop(luaState, 1);

  /* Comentado el hardcodeo para testear el funcionamiento
    int input[17] = { 300, 400, 700, 800, 101, 202, 303, 404, 505, 400, 400, 400, 400, 400, 400, 400, 400};
    this->update(input[rand()%17]);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  */
  }

  lua_close(luaState);
}
