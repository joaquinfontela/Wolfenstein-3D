#ifndef __GAME_H__
#define __GAME_H__

#include <map>
#include <string>
#include <tuple>

#include "../../../../common/includes/PlayerData.h"
#include "../../../../common/includes/Queue/WaitingQueue.h"
#include "../../../../common/includes/YAML/YAMLConfigReader.h"
#include "../../Control/Notification/Notification.h"
#include "../../Control/UpdatableEvent/Updatable.h"
#include "../Map/Map.h"
#include "../Map/MapLoader.h"
#include "../Player/Player.h"

class Updatable;

class Game {
 private:
  static unsigned int nextId;
  std::map<int, Player*> players;
  Map* map;
  YAMLConfigReader yamlConfigReader;
  YAMLMapReader yamlMapReader;
  std::list<Updatable*> updatables;

  // Deberia tener una estructura que maneje los datos del configFile de YAML

 public:
  Game(std::string mapFile, std::string configFile);

  // Fuerza a una puerta a cambiar su estado. Se usa para el cierre automatico
  // de las puertas.
  bool forceDoorStatusChange(int x, int y);

  // Agrega un jugador al mapa de los jugadores
  void addPlayer(int playerID);

  // Changes, if possible, the current weapon of the player.
  void playerSwitchWeapon(int playerID, int weaponPos);

  // Encola la notificacion de los estados de los jugadores que requerian
  // notificar al resto.
  void sendUpdateMessages(WaitingQueue<Notification*>& notis);

  // Elimina a un jugador del mapa de jugadores. Tambien deberia pedirle al mapa
  // que lo borre en sus coordenadas.
  bool removePlayer(int playerID);

  // Moves the rocket missile's position. Returns true if a collision occured and generates the damage accordingly.
  bool moveRocketMissileFrom(double x, double y, double newX, double newY);

  // Actualiza el estado del juego y deja las notificaciones para enviar sobre
  // cambios en el mismo.
  void update(float timeElapsed, WaitingQueue<Notification*>& notis);

  // Actualiza la posicion de los elementos dependientes del tiempo.
  void updatePositions(float timeElapsed, WaitingQueue<Notification*>& notis);

  // Actualiza la velocidad de movimiento del jugador indicado.
  void updatePlayerMoveSpeed(int playerID, double moveSpeed);

  // Actualiza la velocidad de rotacion del jugador indicado.
  void updatePlayerRotationSpeed(int playerID, double rotSpeed);

  // Dispara, si colisiona con un jugador le aplica el daño.
  void playerShoot(int playerID, WaitingQueue<Notification*>& notis);

  // Devuelve el ID de la pared que cambio de estado, -1 si no se modifico nada.
  std::tuple<int, int> moveDoor(int playerID);

  // Comienza el juego.
  void start();

  // Termina el juego.
  void end();

  ~Game();
};

#endif
