#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include <mutex>
#include <vector>

#include "../../../common/includes/Map/Map.h"
#include "../includes/drawable.h"
#include "../includes/player.h"

namespace Lua {

class GameState {
 private:
  std::mutex
      lock;  // Lock para actualizar/leer desde multiples hilos de forma segura.
  Map& matrix;     // Representacion Matricial del mapa.
  Player* player;  // Jugador representado por el script de Lua.
  std::vector<Drawable*>
      seenObjects;  // Vector de objetos que pueden ser observados por el
                    // jugador en ese momento
  double* distanceBuffer;

 public:
  GameState(Map& matrix, Player* self, double* distanceBuffer);

  // Devuelve true si tiene un jugador al alcance de su vista.
  bool playerInSight();

  // Devuelve true si el jugador tiene al alcance de interaccion una puerta.
  bool facingDoor();

  // Devuelve true si el jugador esta proximo a colisionar con una pared en la
  // direccion que esta mirando.
  bool facingWall();

  // Devuelve True si el jugador tiene un item al alcance de su vista.
  bool itemInSight();

  // Agrega un elemento al vector de visibles.
  void addVisibleItem(Drawable* item);

  // Limpia el vector de visibles.
  void clearVisibleItems();
};

}  // namespace Lua

#endif
