#ifndef COMMANDMANAGER_H_
#define COMMANDMANAGER_H_

#include <atomic>

#include "../../common/includes/Socket/SocketWrapper.h"
#include "../../common/includes/Socket/SocketCommunication.h"
#include "../../common/includes/Thread/Thread.h"
#include "scoreboard.h"

/**
 * @brief Abstraction for any class that needs to send and receive information
 * from the server and know if the game is still being played.
 *
 */
class CommandManager : public Thread {
 protected:
  ScoreBoard* scoreboard;
  SocketWrapper socket;
  std::atomic<bool>& alive;

 public:
  CommandManager(ScoreBoard* scoreboard, SocketCommunication& socket,
                 std::atomic<bool>& alive)
      : scoreboard(scoreboard), socket(socket), alive(alive) {}
  ~CommandManager() {}
  virtual void run() = 0;
};

#endif  // COMMANDMANAGER_H_
