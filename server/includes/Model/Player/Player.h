#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../../../../common/includes/PlayerData.h"
#include "../Item/Weapon.h"
#include "../Map/Map.h"


class Map;



class Player {
 private
  double x, y;
  double dirX, dirY;
  double rotSpeed;
  double moveSpeed;
  unsigned int playerID;
  bool hasToBeNotified;
  int score;
  unsigned int health, lifeRemaining, ammo;
  Weapon* weapon;
  bool key;

  int handleDeath(Map& map);

 public:

  // CONSTRUCTORES.
  Player(unsigned int hp, unsigned int lifes, Map& map, unsigned int playerID);
  Player(unsigned int hp, unsigned int lifes);
  Player() {}

  // Recibe daño, si muere y puede respawnear se posiciona sobre su punto de respawn.
  int takeDamage(unsigned int damage, Map& map);

  // GETTERS
  unsigned int ID();
  double getX();
  double getY();
  double getDirX();
  double getDirY();

  // LLena el struct playerdata con toda la informacion relevante para ser transmitida por el socket.
  void fillPlayerData(PlayerData& data);

  // Devuelve cuanto daño hace un ataque con su arma.
  // Si se queda sin balas, cambia de arma.
  int attack();

  // Actualiza la velocidad de movimiento.
  void updateMoveSpeed(double movSpeed);

  // Actualiza la velocidad de rotacion.
  void updateRotationSpeed(double rotSpeed);

  // Equipa el arma indicada.
  void equipWeapon(Weapon* weapon);

  // Comprueba si cierto punto colisiona con el hitbox del jugador.
  bool collidesWith(double x, double y);

  // Devuelve true si hubo un cambio en el estado del jugador que deba ser transmitida al resto.
  bool hasToBeUpdated();

  // Actualiza la posicion del jugador dada la velocidad de movimiento y rotacion.
  void update(Map& map);

  // Equipa una llave.
  void pickupKey();

  // Devuelve si el jugador tiene una llave para abrir puertas.
  bool hasKey();

  // Devuelve true si tiene la maxima cantidad de balas.
  bool hasMaxAmmo();

  // Equipa la municion.
  void pickUpAmmo();

  // Devuelve la vida del jugador.
  int getHealth();

  // Devuelve si el jugador tiene la vida maxima.
  bool hasFullHealth();

  // Agrega vida al jugador. Si se pasa del limite setea la vida al maximo.
  void addHealth(int health);

  // Agrega puntos al jugador.
  void addPoints(int points);

  // Devuelve el puntaje del jugador.
  int getScore();

  ~Player();
};

#endif
