#ifndef COMMANDSENDER_H_
#define COMMANDSENDER_H_

#include "../../common/includes/Socket/SocketCommunication.h"
#include "../../common/includes/Socket/SocketException.h"
#include "../../common/includes/Thread/Thread.h"
#include "scoreboard.h"
#include <atomic>

#include <atomic>

class CommandSender : public Thread {
 public:
  CommandSender(SocketCommunication& s, std::atomic<bool>& alive, ScoreBoard* scoreboard);
  void update(uint32_t keyType);
  virtual void run();
protected:
  ScoreBoard* scoreboard;
  std::atomic<bool>& alive;
  SocketCommunication& socket;

};

#endif  // COMMANDSENDER_H_
