#ifndef __LUA_SENDER_H__
#define __LUA_SENDER_H__

#include "../includes/commandsender.h"
#include "GameState.h"

typedef struct KEY_STATE {
  int W;
  int S;
  int A;
  int D;
} KeyState;

class LuaSender : public CommandSender {
 public:
  LuaSender(SocketCommunication& s, std::atomic<bool>& alive,
            std::string& scriptName, Lua::GameState* gameState)
      : CommandSender(s, alive, nullptr, nullptr, nullptr), scriptName(scriptName) {
    this->gameState = gameState;
  }
  void run();
  void checkForQuit();
  void stopPlayer(KeyState& ks);

 private:
  std::string& scriptName;
  Lua::GameState* gameState;
};

#endif
