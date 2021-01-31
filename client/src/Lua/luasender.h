#ifndef __LUA_SENDER_H__
#define __LUA_SENDER_H__

#include "../commandsender.h"
#include "GameState.h"

class LuaSender : public CommandSender{

public:

  LuaSender(SocketCommunication& s, std::atomic<bool>& alive, std::string& scriptName, Lua::GameState* gameState) : CommandSender(s, alive), scriptName(scriptName){
    this->gameState = gameState;
  }
  void run();
  void checkForQuit();

private:
  std::string& scriptName;
  Lua::GameState* gameState;
};


#endif
