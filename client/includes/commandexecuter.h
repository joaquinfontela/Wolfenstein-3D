#ifndef COMMANDEXECUTER_H_
#define COMMANDEXECUTER_H_

#include <atomic>
#include <map>
#include <mutex>
#include <vector>

#include "../../common/includes/Map/Map.h"
#include "../../common/includes/Socket/SocketCommunication.h"
#include "../../common/includes/Socket/SocketException.h"
#include "../../common/includes/Socket/SocketWrapper.h"
#include "ClientMapLoader.h"
#include "audiomanager.h"
#include "startingscreen.h"
#include "commandmanager.h"
#include "drawablevector.h"
#include "player.h"
#include "playermap.h"
#include "scoreboard.h"

/**
 * @brief Receives the data from the server and calls the other object to keep
 * the game running.
 *
 */
class CommandExecuter : public CommandManager {
 public:
  /**
   * @brief Construct a new Command Executer object.
   *
   * @param s Socket.
   * @param alive True if the game is still running.
   * @param sprites Sprites vector.
   * @param players Players mapped by their ids.
   * @param selfId Our player's id.
   * @param audiomanager Audio manager reference.
   * @param matrix Map reference.
   * @param loader Map loader reference.
   * @param scoreboard Scoreboard reference.
   */
  CommandExecuter(SocketCommunication& s, std::atomic<bool>& alive,
                  DrawableVector& sprites, PlayerMap& players,
                  int selfId, AudioManager& audiomanager, Map& matrix,
                  ClientMapLoader& loader, ScoreBoard* scoreboard,
                  StartingScreen& startingscreen);

  ~CommandExecuter() {}

  /**
   * @brief Starts the music and receives data from the server while the game is
   * being played.
   *
   */
  void run();

  /**
   * @brief Plays a dying sound depending on the player skin and the distance to
   * it.
   *
   * @param gunId Enemy's gun id.
   * @param playerId Enemy's id.
   */
  void playDyingSound(int gunId, int playerId);

  /**
   * @brief Plays the explosion sound.
   *
   */
  void playExplosionSound();

 private:
  /**
   * @brief Receives information about a player from the server. If it already
   * exists it updates it, else it is created with said values.
   *
   */
  void updateOrCreatePlayer();

  /**
   * @brief Disconnects a certain player from the game and deletes it's sprite.
   *
   */
  void disconnectPlayer();

  /**
   * @brief Receives a player id from the server, switches on it's shooting
   * state and plays the shooting sounds.
   *
   */
  void shotsFired();

  /**
   * @brief Receives the coords of a door whose state must be switched.
   *
   */
  void openDoor();

  /**
   * @brief Receives a sprite id and stops it from drawing.
   *
   */
  void pickUpItem();

  /**
   * @brief Renders the death animation of a dying enemy (if the one who died is
   * the users player).
   *
   */
  void playerDied();

  /**
   * @brief Draws new item on the received coordinates.
   *
   */
  void dropItem();

  /**
   * @brief Moves a sprite to the received coordinates.
   *
   */
  void elementSwitchPosition();

  /**
   * @brief Plays the explosion sound and calls the animation rendering.
   *
   */
  void explodeMissile();

  /**
   * @brief Stores the top shooters.
   *
   */
  void saveShotsFired();

  /**
   * @brief Stores the players with the highest score.
   *
   */
  void saveScores();

  /**
   * @brief Stores the top killers.
   *
   */
  void saveKills();

  /**
   * @brief Removes the sprite with the given id.
   *
   * @param itemId Sprite id.
   */
  void removeSpriteWithId(uint32_t itemId);

  /**
   * @brief Pushes to the sprite vector a raycastable explosion animation to be
   * drawn on the received coords.
   *
   * @param itemId Sprite id.
   */
  void renderExplosionAnimation(uint32_t itemId);

  /**
   * @brief Pushes to the sprite vector a raycastable death animation to be
   * drawn on the received coords.
   *
   * @param yamlId Sprite id;
   */
  void renderDeathAnimation(uint32_t playerId);

  /**
   * @brief Swaps the sprite coordinates to the new ones.
   *
   * @param x New X Coordinate.
   * @param y New Y Coordinate.
   * @param itemId Sprite id.
   */
  void renderMovingSprite(double x, double y, uint32_t itemId);

  /**
   * @brief Loads new texture with the given information.
   *
   * @param x X Coordinate on map.
   * @param y Y Coordinate on map.
   * @param yamlId Texture id to be looked up from the yaml loader.
   * @param uniqueId Unique id.
   */
  void loadNewTexture(double x, double y, uint32_t yamlId, uint32_t uniqueId);

  /**
   * @brief Plays the shooting sounds depending on the distance to the enemy.
   *
   * @param shooterId Enemy id.
   */
  void playShootingSounds(int shooterId);

  /**
   * @brief Reproduces the door opening sound depending on the distance.
   *
   * @param x
   * @param y
   */
  void playDoorOpeningSound(int x, int y);

  SocketWrapper infogetter;
  StartingScreen& startingscreen;
  DrawableVector& sprites;
  PlayerMap& players;
  int selfId;
  AudioManager& audiomanager;
  Map& matrix;
  ClientMapLoader& loader;
};

typedef std::map<uint32_t, Player*>::iterator iterator_t;

#endif  // COMMANDEXECUTER_H_
