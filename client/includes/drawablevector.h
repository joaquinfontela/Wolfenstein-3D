#ifndef DRAWABLEVECTOR_H_
#define DRAWABLEVECTOR_H_

#include <mutex>
#include <vector>

#include "drawable.h"

/**
 * @brief Holds the vector of drawable sprites and a lock, since this is a
 * shared attribute in many threads.
 *
 */
class DrawableVector {
 private:
  std::mutex lock;
  std::vector<Drawable*>& sprites;

  /**
   * @brief Deletes all the sprites dynamically allocated.
   *
   * @param sprites List of values to be deleted.
   */
  void garbageCollector();

 public:
  /**
   * @brief Construct a new Drawable Vector object.
   *
   * @param sprites Sprite vector.
   * @param lock Mutex.
   */
  DrawableVector(std::vector<Drawable*>& sprites)
      : sprites(sprites) {}

  /**
   * @brief Raycasts the sprites from the information given.
   *
   * @param x Player X Coord.
   * @param y Player Y Coord.
   * @param dirX Player's X Direction Coord.
   * @param dirY Player's Y Direction Coord.
   * @param planeX Player's X Plane Coord.
   * @param planeY Player's Y Plane Coord.
   * @param distanceBuffer Buffer with all the distances calculated from the
   * raycaster; maps each position to the distance of the first visible object.
   * @param drawableDiff Time passed since the last call.
   * @param manager Texture manager reference.
   */
  void raycastSprites(double x, double y, double dirX, double dirY,
                      double planeX, double planeY, double* distanceBuffer,
                      float drawableDiff, TextureManager& manager);
  /**
   * @brief Pushes new sprite to the list.
   *
   * @param drawable Sprite to be stored.
   */
  void push_back(Drawable* drawable);

  /**
   * @brief Erases and pops element from vector.
   *
   * @param tokill Element to destroy.
   */
  void popAndErase(Drawable* tokill);

  /**
   * @brief Pops sprite from the vector and identifies the sound it should make.
   *
   * @param itemId Sprite id.
   * @param soundId Pointer to store the sound the sprite makes.
   */
  void removeSpriteWithIdAndGetSound(uint32_t itemId, uint32_t* soundId);

  /**
   * @brief Sets the X and Y attributes of the sprite.
   *
   * @param x New sprite's x coord.
   * @param y New sprite's y coord.
   * @param itemId Sprite id.
   */
  void swapCoords(double x, double y, uint32_t itemId);

  /**
   * @brief Get the sprite coords and erase it afterwards.
   *
   * @param x Stores the x coord.
   * @param y Stores the y coord.
   * @param itemId Sprite id.
   */
  void getCoordsAndErase(double* x, double* y, uint32_t itemId);

  /**
   * @brief Releases all the resources.
   *
   */
  ~DrawableVector();
};

#endif  // DRAWABLEVECTOR_H_
