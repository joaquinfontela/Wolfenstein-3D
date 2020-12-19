#ifndef COMMANDSENDER_H_
#define COMMANDSENDER_H_

#include "../../common/includes/Socket/SocketCommunication.h"
#include "../../common/includes/Socket/SocketException.h"
#include "../../common/includes/Thread/Thread.h"

class CommandSender {
 public:
  CommandSender(SocketCommunication& s);
  //~CommandSender() {}
  void run();

 private:
  void update();
  SocketCommunication& socket;
  uint32_t x;
  uint32_t y;
};

#endif  // COMMANDSENDER_H_
