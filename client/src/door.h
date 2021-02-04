#ifndef DOOR_H_
#define DOOR_H_

#include <cstring>

#include "../../common/includes/Map/Map.h"
#include "clientprotocol.h"
#include "drawable.h"

/**
 * @brief Raycastable door.
 *
 */
class Door : public Drawable {
 public:
  /**
   * @brief Construct a new Door object
   *
   * @param matrixXCoord X Coordinate for the map matrix.
   * @param matrixYCoord Y Coordinate for the map matrix.
   * @param width Screen width in pixels.
   * @param height Screen height in pixels.
   * @param side Whether the wall was hit by a ray through the side or not.
   * @param i Pixel column being renderer.
   * @param matrix Reference to the map.
   */
  Door(int matrixXCoord, int matrixYCoord, const int& width, const int& height,
       const int& dx, const int& dy, int side, const double& cameraXCoord,
       const int& i, Map* matrix)
      : Drawable(matrixXCoord, matrixYCoord, DOOR),
        matrixXCoord(matrixXCoord),
        matrixYCoord(matrixYCoord),
        width(width),
        height(height),
        cameraXCoord(cameraXCoord),
        dx(dx),
        dy(dy),
        side(side),
        i(i),
        matrix(matrix) {}

  /**
   * @brief Raycasts the door onto the screen.
   *
   * @param manager Reference to the texture manager.
   * @param x Player X coordinate.
   * @param y Player Y coordinate.
   * @param dirX Player's direction X coordinate.
   * @param dirY Player's direction Y coordinate.
   * @param planeX Player's plane X coordinate.
   * @param planeY Player's plane Y coordinate.
   * @param distanceBuffer Array that maps each position to the distance to the
   * first drawable element on the i-th pixel column.
   * @param diff Time passed since the last iteration.
   */
  void draw(TextureManager& manager, double x, double y, double dirX,
            double dirY, double planeX, double planeY, double* distanceBuffer,
            float diff = 0) override;

  /**
   * @brief Coordinates for the map matrix.
   *
   */
  int matrixXCoord, matrixYCoord;

  /**
   * @brief Iteration index.
   *
   */
  const int& i;

 private:
  const int &width, height;
  const double& cameraXCoord;
  const int &dx, dy;
  int side;
  Map* matrix;
};

#endif  // DOOR_H_
