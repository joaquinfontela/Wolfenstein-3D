#ifndef COMMANDSENDER_H_
#define COMMANDSENDER_H_

#include <atomic>

#include "../../common/includes/Socket/SocketCommunication.h"
#include "../../common/includes/Socket/SocketException.h"
#include "commandmanager.h"
#include "scoreboard.h"
#include "startingscreen.h"
#include "player.h"

/**
 * @brief Class that takes the user input and sends it to the server.
 *
 */
class CommandSender : public CommandManager {
 public:
  /**
   * @brief Construct a new Command Sender object
   *
   * @param s Socket.
   * @param alive True if the game is still being played.
   * @param scoreboard Reference to the scoreboard drawer.
   */
  CommandSender(SocketCommunication& s, std::atomic<bool>& alive,
                ScoreBoard* scoreboard, Player* player, StartingScreen* startingscreen);

  /**
   * @brief Sends through the socket the user input encoded on a uint32_t.
   *
   * @param keyType Key press code.
   */
  void update(uint32_t keyType);

  /**
   * @brief While the game is being played, this method reads the player input
   * and redirects it to the update method. If the player quits the window it
   * sets the alive boolean reference to false and stops the scoreboard from
   * drawing.
   *
   */
  virtual void run();

 private:
  Player* player;
  StartingScreen* startingscreen;
};

#endif  // COMMANDSENDER_H_
