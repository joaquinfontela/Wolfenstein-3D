#ifndef TP_FINAL_MAP_H
#define TP_FINAL_MAP_H

#include <string>
#include <vector>

#include "Tile/Tile.h"

#include "../Player/Player.h"

class Tile;
class Player;


typedef std::vector<std::vector<Tile>> TileMatrix;

class Map {
 public:
  Map(int dimx, int dimy);
  void addDropWithIdAt(int id, int x, int y);
  //std::vector<ItemDrop> getItemDropsAt(int x, int y);

  // Mueve un jugador de (fromX, fromY) a (x, y)
  bool moveTo(double fromX, double fromY, double x, double y, Player* p);

  // Verifica si las coordenadas (x, y) se salen de los limites del mapa.
  void verifyCoordinateDoesNotSurpassMapLimits(int x, int y);

  // Agrega un jugador al mapa.
  void addPlayer(int x, int y, Player* p);

  // Devuelve una tupla representando el (x, y) sobre el cual el jugador deberia respawnear.
  std::tuple<double, double> handleRespawn();

  // Devuelve la primera instancia del jugador que colisiona con la bala emitida desde attacker. Nullptr si no colisiona con ningun jugador.
  Player* traceAttackFrom(Player* attacker);

 private:
  int dimx;
  int dimy;
  TileMatrix tileMatrix;
};

#endif  // TP_FINAL_MAP_H
