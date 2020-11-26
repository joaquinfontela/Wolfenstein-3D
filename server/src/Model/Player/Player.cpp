#include "../../../includes/Model/Player/Player.h"

Player::Player(unsigned int hp, unsigned int lifes)
    : health(hp), lifeRemaining(lifes), hasKey(false) {}

int Player::handleDeath() {
  if (this->lifeRemaining == 0) {
    this->health = 0;
    return -1;  // El jugador ya no puede respawnear.
  }

  this->lifeRemaining -= 1;
  this->health = 100;  // Deberia restaurar la vida al maximo.
  return 0;            // Devuelvo valor indicando que mi vida quedo en 0.
}
int Player::takeDamage(unsigned int damage) {
  if (damage >= this->health) {
    return handleDeath();
  }

  this->health -= damage;
  return this->health;
}

int Player::attack() {
  // Deberia pedirle a su arma que ataque, devolviendo el daño que hizo.
  // Luego le pregunto al arma cuantas balas tiene, si no tiene mas disponible,
  // cambio a cuchillo
}

void Player::pickupKey() { this->hasKey = true; }

int Player::getHealth() { return this->health; }