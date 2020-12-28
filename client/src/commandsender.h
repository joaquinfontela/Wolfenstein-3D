#ifndef COMMANDSENDER_H_
#define COMMANDSENDER_H_

#include "../../common/includes/Socket/SocketCommunication.h"
#include "../../common/includes/Socket/SocketException.h"
#include "../../common/includes/Thread/Thread.h"
#include <atomic>

class CommandSender : public Thread {
 public:
  CommandSender(SocketCommunication& s, std::atomic<bool>& alive);
  CommandSender(SocketCommunication& s);
  void update(uint32_t keyType);
  void run();

 private:
  std::atomic<bool>& alive;
  SocketCommunication& socket;

};

#endif  // COMMANDSENDER_H_
