#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../common/includes/PlayerData.h"
#include "clientprotocol.h"
#include "drawable.h"

/**
 * @brief [CLIENT SIDE] Player class. Holds important information about each
 * player and is able to raycast it if it's an enemy.
 *
 */
class Player : public Drawable {
 public:
   bool minigunShooting = false;

  /**
   * @brief [CLIENT SIDE]  Construct a new Player object
   *
   * @param posX Player's X Coordinate.
   * @param posY Player's Y Coordinate.
   * @param dirX Player's X Direction Coordinate.
   * @param dirY Player's Y Direction Coordinate.
   * @param planeX Player's X Plane Coordinate.
   * @param planeY Player's Y Plane Coordinate.
   * @param id Player id.
   */
  Player(double posX, double posY, double dirX, double dirY, double planeX,
         double planeY, int id)
      : Drawable(posX, posY, 3, id),
        shooting(false),
        dirX(dirX),
        dirY(dirY),
        planeX(planeX),
        planeY(planeY),
        score(0),
        playerID(id),
        health(100),
        lives(2),
        moving(false),
        bullets(8),
        hasTheKey(false),
        healthdown(false),
        timePassed(0),
        totalFrames(TIME_PER_ANIMATION_SLIDE * 5),
        frames(-1),
        framesPerAnimation(1),
        animatingShooting(false),
        animatingMovement(false) {}

  ~Player() {}

  /**
   * @brief [CLIENT SIDE] Construct a new Player object
   *
   * @param info Information taken from the server. Used for creating enemies.
   */
  Player(PlayerData& info);

  /**
   * @brief [CLIENT SIDE] Updates the player info.
   *
   * @param info Info carried from the server.
   */
  void update(PlayerData& info);

  /**
   * @brief [CLIENT SIDE] Draws the player using the raycasting algorithm.

   * @param manager Reference to the texture manager.
   * @param posX Player's X coordinate.
   * @param posY Player's Y coordinate.
   * @param dirX Player's X direction coordinate.
   * @param dirY Player's Y direction coordinate.
   * @param planeX Player's X plane coordinate.
   * @param planeY Player's Y plane coordinate.
   * @param distanceBuffer Array containing the distances to the first drawable
   * object on each pixel column.
   * @param diff Time passed.
   */
  void draw(TextureManager& manager, double posX, double posY, double dirX,
            double dirY, double planeX, double planeY, double* distanceBuffer,
            float diff) override;

  /**
   * @brief [CLIENT SIDE] Gets the Soldier Id.
   *
   * @return int Soldier id.
   */
  int getSoldierId();

  /**
   * @brief [CLIENT SIDE] Calculates the distance between players.
   *
   * @param other
   * @return double distance to the other player.
   */
  double calculateDist(Player* other);

  /**
   * @brief [CLIENT SIDE] Calculates the distance from the player to the given
   * coordinates.
   *
   * @param otherx X entity coordinate.
   * @param othery Y entity coordinate.
   * @return double distance to the entity.
   */
  double calculateDist(int otherx, int othery);

  /**
   * @brief [CLIENT SIDE] Sets the shooting boolean to true.
   *
   */
  void startShooting();

  /**
   * @brief [CLIENT SIDE] Sets the shooting boolean to false.
   *
   */
  void stopShooting();

  /**
   * @brief [CLIENT SIDE] Checks whether the player is sgooting or not.
   *
   * @return true if it's shooting.
   * @return false otherwise.
   */
  bool isShooting();

  /**
   * @brief [CLIENT SIDE] Checks whether the player is moving or not.
   *
   * @return true if it's moving.
   * @return false otherwise.
   */
  bool isMoving();

  /**
   * @brief [CLIENT SIDE] Sets the movement boolean to false.
   *
   */
  void stopMoving();

  /**
   * @brief [CLIENT SIDE] Returns false.
   *
   * @return false
   */
  bool hasThisUniqueId(int otherid) override;

  /**
   * @brief [CLIENT SIDE] Returns false.
   *
   * @return false
   */
  bool isSprite() override;

  /**
   * @brief [CLIENT SIDE] Returns true.
   *
   * @return true
   */
  bool isPlayer() override;

  /**
   * @brief [CLIENT SIDE] Checks for the key.
   *
   * @return true if the player has the key.
   * @return false if the player doesn't have the key.
   */
  bool hasKey();

  int playerID;
  int weaponId;
  double dirX;
  double dirY;
  double planeX;
  double planeY;
  int health;
  int lives;
  int bullets;
  int score;
  bool moving;
  int healthdown;
  bool key;

 private:
  /**
   * @brief [CLIENT SIDE] Restarts all the attributes that animate the player or
   * indicate some sort of movement or shooting status.
   *
   */
  void restartAnimationStats();

  /**
   * @brief [CLIENT SIDE] True if any of those actions is happening.
   *
   */
  bool animatingShooting, animatingMovement, shooting;

  /**
   * @brief [CLIENT SIDE] Frames per animation for the raycasted enemy.
   *
   */
  int framesPerAnimation;
  int frames;
  int totalFrames;
  float timePassed;
  bool hasTheKey;
  Area srcArea, destArea;
};

#endif  // PLAYER_H_
