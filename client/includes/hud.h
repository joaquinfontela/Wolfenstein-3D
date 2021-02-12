#ifndef HUD_H_
#define HUD_H_

#include "area.h"
#include "audiomanager.h"
#include "player.h"
#include "HudAnimations.h"
#include "texturemanager.h"

/**
 * @brief Renders all the images that appear in the hud.
 *
 */
class Hud {
 private:
  int weaponId;
  Player* player;
  TextureManager& manager;
  AudioManager& audiomanager;
  HudAnimations hudgun;
  HudAnimations bjface;
  HudAnimations gun;
  short animationStatus;
  short movementStatus;
  int fps;
  int framesAlreadyPlayed;
  int screenHeight, screenWidth;
  Area area;
   /**
    * @brief Computes the frame to render for the shooting gun.
    *
    * @return int frame to render.
    */
  int getGunFrame();

  /**
   * @brief Plays shooting sound from the player's gun.
   *
   */
  void playMyShootingSound();

  /**
   * @brief Renders the fps counter on the hud.
   *
   */
  void renderFpsCounter();

  /**
   * @brief Renders the amount of lives remaining the player has.
   *
   */
  void renderLifes();

  /**
   * @brief Plays the face animation depending on the player's health.
   *
   */
  void renderFace();

  /**
   * @brief Renders the health on the hud.
   *
   */
  void renderHealth();

  /**
   * @brief Renders the type of gun being used on the hud.
   *
   */
  void renderTypeOfGun();

  /**
   * @brief Decides how the player's gun shall be rendered. Checks if the player
   * is still moving or if it the current animation playing has ended.
   *
   */
  void renderGun();

  /**
   * @brief Renders the player score on the hud.
   *
   */
  void renderScore();

  /**
   * @brief Renders gun on screen.
   *
   * @param dx Amount by which the x coordinate of the shooting sprite is
   * shifted.
   * @param dy Amount by which the y coordinate of the shooting sprite is
   * shifted.
   */
  void renderGunWithShifts(int dx = 0, int dy = 0, int updatefreq = 16);

  /**
   * @brief Calls renderGunWithShifts, using the first two parameters to give a
   * moving sensation by using continuous shifts
   *
   */
  void renderGunWithMovement();

  /**
   * @brief Renders the hud border.
   *
   */
  void renderBorder();

  /**
   * @brief Renders the key on the hud, if the player has it.
   *
   */
  void renderKey();

  /**
   * @brief Renders the amount of bullets left on the hud.
   *
   */
  void renderBullets();

  /**
   * @brief Updates the gunid identified by the hud, changing it from the
   * player's gun id.
   *
   */
  void updateGunId();

  /**
   * @brief Whenever the player gets hit, there will be a small amount of blood
   * being drawn on the window.
   *
   */
  void renderBloodDamage();

 public:
  /**
   * @brief Updates the fps counter.
   *
   * @param fps Fps counter.
   */
  void updateFpsCounter(int fps);

  /**
   * @brief Updates the gun frame about to be played.
   *
   */
  void updateHudGun();

  /**
   * @brief Updates hud's player frame about to be played.
   *
   */
  void updateBjFace();

  /**
   * @brief Calls the drawing methods
   *
   */
  void update();

  /**
   * @brief Construct a new Hud object
   *
   * @param window Reference to the window.
   * @param player Reference to the user's playing.
   * @param manager Reference to the texture manager.
   * @param audiomanager Reference to the audio manager.
   */
  Hud(Player* player, TextureManager& manager, AudioManager& audiomanager);
};

#endif  // HUD_H_
