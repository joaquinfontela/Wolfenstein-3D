#ifndef RAYCASTEDANIMATION_H_
#define RAYCASTEDANIMATION_H_

#include "clientprotocol.h"
#include "drawable.h"
#include "texturemanager.h"

/**
 * @brief Instances of this class are raycastable animations.
 *
 */
class RaycastedAnimation : public Drawable {
 public:
  /**
   * @brief Construct a new Raycasted Animation object
   *
   * @param x Raycastable x coordinate.
   * @param y Raycastable y coordinate.
   * @param executer Reference to the command executer.
   * @param itemId Texture id.
   * @param uniqueid Unique sprite id.
   * @param framesPerAnimation Amount of frames the animation has.
   */
  RaycastedAnimation(double x, double y, int itemId,
                     int uniqueid, int framesPerAnimation)
      : Drawable(x, y, itemId, uniqueid),
        totalFrames(TIME_PER_ANIMATION_SLIDE * FRAMES_PER_EXPLOSION_ANIMATION),
        frames(0),
        framesPerAnimation(framesPerAnimation),
        timePassed(0) {}

  /**
   * @brief Raycasts the actual frame of the animation.
   *
   * @param manager Texture manager reference.
   * @param posX Player X coordinate.
   * @param posY Player Y coordinate.
   * @param dirX Player's direction X coordinate.
   * @param dirY Player's direction Y coordinate.
   * @param planeX Player's plane X coordinate.
   * @param planeY Player's plane Y coordinate.
   * @param distanceBuffer Array that maps each position to the distance to the
   * first drawable element on the i-th pixel column.
   * @param diff Time passed since the last iteration.
   */
  void draw(TextureManager& manager, double posX, double posY, double dirX,
            double dirY, double planeX, double planeY, double* distanceBuffer,
            float diff) override;

 private:
  int framesPerAnimation;
  int frames;
  int totalFrames;
  float timePassed;
};

#endif  // RAYCASTEDANIMATION_H_
