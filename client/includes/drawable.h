#ifndef DRAWABLE_H_
#define DRAWABLE_H_
#include <climits>

#include "area.h"
#include "texturemanager.h"

/**
 * @brief Represents a non-wall nor door raycastable entity.
 *
 */
class Drawable {
 public:
  double x;
  double y;
  int id;
  double dist;
  int uniqueid;
  bool hasToBeDeleted;

  Drawable() {}
  ~Drawable() {}
  Drawable(double x, double y, int id, int uniqueid = 0, double dist = INT_MAX)
      : x(x),
        y(y),
        id(id),
        dist(dist),
        uniqueid(uniqueid),
        hasToBeDeleted(false) {}

  /**
   * @brief Draws the object using the raycasting algorithm.
   *
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
  virtual void draw(TextureManager& manager, double posX, double posY,
                    double dirX, double dirY, double planeX, double planeY,
                    double* distanceBuffer, float diff);

  /**
   * @brief Compares objects depending on the distance.
   *
   * @param other
   * @return true if this->dist is greater other.dist
   * @return false if this->dist is equal or less other.dist
   */
  bool operator<(Drawable& other);

  /**
   * @brief Verifies if the drawable object is visible within the players field
   * of view.
   *
   * @param distanceBuffer
   * @param posX
   * @param posY
   * @param dirX
   * @param dirY
   * @param planeX
   * @param planeY
   * @param width
   * @param height
   * @return true if the drawable object is visible.
   * @return false if the drawable object is not visible.
   */
  bool isContained(double* distanceBuffer, double posX, double posY,
                   double dirX, double dirY, double planeX, double planeY,
                   int width, int height);

  void loadDistanceWithCoords(int px, int py);
  void getPreCalculatedValues(int& preCalcdValue1, int& preCalcdValue2,
                              int& preCalcdValue3, bool& tooFar, int spriteScreen,
                              int spriteHeight, int spriteWidth, int height);
  virtual bool hasThisUniqueId(int otherid);
  virtual bool isSprite();
  virtual bool isPlayer();

 protected:
  void calculateDrawingData(int& spriteScreen, int& spriteWidth,
                            int& spriteHeight, int& drawStart, int& drawEnd,
                            double& transformY, double posX, double posY,
                            double planeX, double planeY, double dirX,
                            double dirY, int width, int height);
  Area srcArea, destArea;
};

#endif  // DRAWABLE_H_
