#ifndef __GAME_H__
#define __GAME_H__

#include <map>
#include <string>
#include <tuple>

#include "../../../../common/includes/PlayerData.h"
#include "../../../../common/includes/Queue/WaitingQueue.h"
#include "../../../../common/includes/YAML/YAMLConfigReader.h"
#include "../../Control/Notification/Notification.h"
#include "../../Control/Notification/ScoreBoard.h"
#include "../../Control/UpdatableEvent/Updatable.h"
#include "../Map/Map.h"
#include "../Map/MapLoader.h"
#include "../Player/Player.h"

class Updatable;

/**
	* @section DESCRIPTION
  * Class that represents the game as a whole.
  */
class Game {
 private:
  static unsigned int nextId;
  std::map<int, Player*> players;
  Map* map;
  YAMLConfigReader yamlConfigReader;
  YAMLMapReader yamlMapReader;
  std::list<Updatable*> updatables;
  bool started;

 public:
  Game(std::string mapFile, std::string configFile);

  /**
	* <Sets the status of a given player as shooting>
	*
	* @param Player ID of the intended player.
	* @param The status to set the player.
  */
  void setShooting(int playerID, bool shooting);

  /**
	* <Forces the status of a door to change>
	*
	* @param X Coordinate of the door.
	* @param Y Coordiante of the door.
  */
  bool forceDoorStatusChange(int x, int y);

  /**
	* <Generates a radial damage from a center point>
	*
	* @param X Coordinate of the center.
	* @param Y Coordinate of the center.
  * @param The notification Queue on which to notify of change if needed.
  */
  void generateRadiusDamage(int x, int y, WaitingQueue<Notification*>& notif);

  // Agrega un jugador al mapa de los jugadores
  void addPlayer(int playerID, WaitingQueue<Notification*>& notis);

  /**
	* <Switches current weapon of the player to the specified slot>
	*
	* @param Player ID of the intended player.
	* @param Weapon slot to set as active.
  */
  void playerSwitchWeapon(int playerID, int weaponPos);

  /**
	* <Queues update messages of the status of the players>
	*
  * @param The notification Queue on which to notify of change if needed.
  */
  void sendUpdateMessages(WaitingQueue<Notification*>& notis);

  /**
	* <Queues update messages of the status of the game.>
	*
  * @param The notification Queue on which to notify of change if needed.
  */
  void sendGameStatus(WaitingQueue<Notification*>& notis);

  /**
	* <Removes a player from the game.>
	*
	* @param Player ID of the intended player to remove.
  * @return Boolean if the player was removed.
  */
  bool removePlayer(int playerID);

  /**
	* <Moves the rocket missile from (x, y) to (newX, newY) if possible>
	*
	* @param Initial X Coordinate.
	* @param Initial Y Coordinate.
  * @param Final X Coordinate.
  * @param Final Y Coordinate.
  * @param Notification Queue to inform of changes.
  * @return Boolean representing if the move was possible.
  */
  bool moveRocketMissileFrom(double x, double y, double newX, double newY, WaitingQueue<Notification*>& notif);

  /**
	* <Updates the game status given an elapdsed time>
	*
	* @param Time elapsed in seconds since last update.
  * @param The notification Queue on which to notify of change if needed.
  */
  void update(float timeElapsed, WaitingQueue<Notification*>& notis);

  /**
	* <Updates the position of all players through time>
	*
	* @param Time elapsed in seconds since last update.
  * @param The notification Queue on which to notify of change if needed.
  */
  void updatePositions(float timeElapsed, WaitingQueue<Notification*>& notis);

  /**
	* <Changes the movement speed of a player>
	*
	* @param Player ID of the intended player.
  * @param Movement speed value to add to the player.
  */
  void updatePlayerMoveSpeed(int playerID, double moveSpeed);

    /**
	* <Changes the rotation speed of a player>
	*
	* @param Player ID of the intended player.
  * @param Rotation speed value to add to the player.
  */
  void updatePlayerRotationSpeed(int playerID, double rotSpeed);

  /**
	* <Shoots from the position and direction of the player>
	*
	* @param Player ID of the intended player.
  * @param Notification Queue to notify of changes.
  */
  void playerShoot(int playerID, WaitingQueue<Notification*>& notis);

  /**
	* <Opens, if possible, a door from the position of a player>
	*
	* @param Player ID of the intended player.
  * @return Tuple representing the coordinate (x, y) of the affected door. (-1, -1) if change was not possible.
  */
  std::tuple<int, int> moveDoor(int playerID);

  /**
	* <Checks if game has already begun>
	*
  * @return Bool to represent if the game has begun or not.
  */
  bool hasStarted();

  /**
	* <Starts the game, if possible. Only the first player to connect is given admin rights>
	*
	* @param Player ID of the intended player.
  * @param Notification Queue to notify of changes.
  */
  void start(int playerID, WaitingQueue<Notification*>& notif);

  ScoreBoard* generateKillScoreboard(std::vector<Player*>& players);
  ScoreBoard* generateScoreboard(std::vector<Player*>& players);
  ScoreBoard* generateShotsFiredScoreBoard(std::vector<Player*>& players);

  /**
	* <Ends the game, generating specific leaderboards of the events that happened>
	*
  */
  void end(WaitingQueue<Notification*>& queue);

  ~Game();
};

#endif
