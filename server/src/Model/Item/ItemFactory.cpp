#include "../../../includes/Model/Item/ItemFactory.h"

#include <iostream>

#include "../../../includes/Model/Item/Ammo.h"
#include "../../../includes/Model/Item/Blood.h"
#include "../../../includes/Model/Item/Chest.h"
#include "../../../includes/Model/Item/Cross.h"
#include "../../../includes/Model/Item/Crown.h"
#include "../../../includes/Model/Item/Cup.h"
#include "../../../includes/Model/Item/Food.h"
#include "../../../includes/Model/Item/Key.h"
#include "../../../includes/Model/Item/Kit.h"

ItemFactory::ItemFactory()
    : yamlConfigReader(std::string("/usr/local/share/Wolfenstein/YAML/config.yaml")) {}

ItemFactory::ItemFactory(std::string& configFileName)
    : yamlConfigReader(configFileName) {}

Item* ItemFactory::getItem(int itemTypeId, int uniqueId) {
  switch (itemTypeId) {
    case 101:
      return new Ammo(itemTypeId, uniqueId);
      break;

    case 102:
      return new Blood(itemTypeId,
          uniqueId, yamlConfigReader.getHealthSumWhenPickingUpItem(102),
          yamlConfigReader.getMaxHealthToBeAbleToPickUpBloodItem());
      break;

    case 103:
      return new Chest(itemTypeId, uniqueId,
                       yamlConfigReader.getPointsSumWhenPickingUpItem(103));
      break;

    case 104:
      return new Cross(itemTypeId, uniqueId,
                       yamlConfigReader.getPointsSumWhenPickingUpItem(104));
      break;

    case 105:
      return new Crown(itemTypeId, uniqueId,
                       yamlConfigReader.getPointsSumWhenPickingUpItem(105));
      break;

    case 106:
      return new Cup(itemTypeId, uniqueId,
                     yamlConfigReader.getPointsSumWhenPickingUpItem(106));
      break;

    case 107:
      return new Food(itemTypeId, uniqueId,
                      yamlConfigReader.getHealthSumWhenPickingUpItem(107));
      break;

    case 108:
      return new Key(itemTypeId, uniqueId);
      break;

    case 109:
      return new Kit(itemTypeId, uniqueId,
                     yamlConfigReader.getHealthSumWhenPickingUpItem(109));
      break;

    default:
      return nullptr;
      break;
  }
}
