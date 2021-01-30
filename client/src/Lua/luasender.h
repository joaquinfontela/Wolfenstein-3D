#ifndef __LUA_SENDER_H__
#define __LUA_SENDER_H__

#include "../commandsender.h"

class LuaSender : public CommandSender{

public:

  LuaSender(SocketCommunication& s, std::atomic<bool>& alive, std::string& scriptName) : CommandSender(s, alive), scriptName(scriptName){}
  void run();
  void checkForQuit();

private:
  std::string& scriptName;
};


#endif
