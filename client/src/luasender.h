#ifndef __LUA_SENDER_H__
#define __LUA_SENDER_H__

#include "commandsender.h"

class LuaSender : public CommandSender{

public:

  LuaSender(SocketCommunication& s, std::atomic<bool>& alive) : CommandSender(s, alive){}
  void run();
  void checkForQuit();
};


#endif
