#ifndef TP_FINAL_MAP_H
#define TP_FINAL_MAP_H

#include <cstdlib>
#include <string>
#include <vector>

#include "../../../../common/includes/Queue/WaitingQueue.h"
#include "../../../../common/includes/YAML/YAMLMapReader.h"
#include "../../Control/Notification/Notification.h"
#include "../Player/Player.h"
#include "Tile/Tile.h"

class Tile;
class Player;
class Item;
class Wall;

typedef std::vector<std::vector<Tile>> TileMatrix;

class Map {
 public:
  Map(int dimx, int dimy);
  void addItemDropAt(Item* item, int x, int y);
  void addWeaponDropAt(Weapon* weapon, int x, int y);
  void addDoorAt(Door* door, int x, int y);
  void addWallAt(Wall* wall, int x, int y);

  void addAmmoDropAt(int x, int y);
  void addKeyDropAt(int x, int y);

  void addAmmoDropAt(int x, int y, WaitingQueue<Notification*>& notis);
  void addKeyDropAt(int x, int y, WaitingQueue<Notification*>& notis);

  void removePlayer(int x, int y, Player* p);

  bool forceDoorStatusChange(int x, int y);

  void setRespawnPoints(std::vector<Coordinate> respPoints);

  // Mueve un jugador de (fromX, fromY) a (x, y)
  bool moveTo(double fromX, double fromY, double x, double y, Player* p,
              WaitingQueue<Notification*>& notis);

  // Mueve un elemento, utilizado para el movimiento de elementos distintos del Jugador.
  bool moveTo(double fromX, double fromY, double x, double y);

  // Verifica si las coordenadas (x, y) se salen de los limites del mapa.
  void verifyCoordinateDoesNotSurpassMapLimits(int x, int y);

  // Agrega un jugador al mapa.
  void addPlayer(int x, int y, Player* p);

  // Devuelve una tupla representando el (x, y) sobre el cual el jugador deberia
  // respawnear.
  std::tuple<double, double> handleRespawn();

  // Intenta abrir una puerta directamente en frente del jugador y devuelve el
  // (x, y) de la puerta si se abrio. (-1, -1) caso contrario.
  std::tuple<int, int> moveDoor(Player* p);

  // Devuelve la primera instancia del jugador que colisiona con la bala emitida
  // desde attacker. Nullptr si no colisiona con ningun jugador.
  Player* traceAttackFrom(Player* attacker, int range);

  static unsigned int getAndIncreaseByOneNextUniqueItemId();

 private:
  static unsigned int nextId;
  std::vector<Coordinate> respawnPoints;
  int dimx;
  int dimy;
  TileMatrix tileMatrix;
  Coordinate getRandomRespawn();
  bool tileHasPlayers(Coordinate& c);
};

#endif  // TP_FINAL_MAP_H
