#include "../../includes/YAML/YAMLConfigReader.h"

#include <iostream>

YAMLConfigReader::YAMLConfigReader(std::string fileName) {
  this->fileName = fileName;
  data = this->getData();
}

YAML::Node YAMLConfigReader::getData() {
  return YAML::LoadFile(this->fileName);
}

int YAMLConfigReader::getBulletAmountAtStart() {
  return data["BULLET_AMOUNT_AT_START"].as<int>();
}

int YAMLConfigReader::getBulletAmountDropWhenPlayerDies() {
  return data["BULLET_DROP_WHEN_DEATH"].as<int>();
}

int YAMLConfigReader::getMaxAmountOfBullets() {
  return data["MAX_BULLETS"].as<int>();
}

int YAMLConfigReader::getPointsPerKill(){
  return data["POINTS_PER_KILL"].as<int>();
}

int YAMLConfigReader::getBulletAmountWhenPickUpAmmo() {
  return data["AMMO_PICK_UP"].as<int>();
}

int YAMLConfigReader::getMaxHealth() { return data["MAX_HEALTH"].as<int>(); }

int YAMLConfigReader::getMaxReviveTimes() {
  return data["MAX_REVIVE"].as<int>();
}

int YAMLConfigReader::getMaxHealthToBeAbleToPickUpBloodItem() {
  return data["MAX_HEALTH_TO_PICK_UP_BLOOD"].as<int>();
}

int YAMLConfigReader::getHealthSumWhenPickingUpItem(int itemId) {
  return data["HEALTH_SUM_WHEN_PICK_UP_ITEM"][itemId].as<int>();
}

int YAMLConfigReader::getPointsSumWhenPickingUpItem(int itemId) {
  return data["POINTS_SUM_WHEN_PICK_UP_ITEM"][itemId].as<int>();
}

std::vector<int> YAMLConfigReader::getMinAndMaxDamagePerBullet() {
  std::vector<int> bulletDamageLimits;
  bulletDamageLimits.push_back(data["DAMAGE_PER_BULLET_MIN"].as<int>());
  bulletDamageLimits.push_back(data["DAMAGE_PER_BULLET_MAX"].as<int>());
  return bulletDamageLimits;
}

float YAMLConfigReader::getBlastFrequency(int weaponId) {
  return data["BLAST_FREQ"][weaponId].as<float>();
}

int YAMLConfigReader::getShotsPerBlast(int weaponId) {
  return data["SHOTS_PER_BLAST"][weaponId].as<int>();
}

int YAMLConfigReader::ammoLostPerShot(int weaponId) {
  return data["AMMO_LOST_PER_SHOT"][weaponId].as<int>();
}

float YAMLConfigReader::precision(int weaponId) {
  return data["PRECISION"][weaponId].as<float>();
}

float YAMLConfigReader::getMatchLength(){
  return data["MATCH_LENGTH"].as<float>();
}
