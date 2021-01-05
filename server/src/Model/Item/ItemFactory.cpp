#include "../../../includes/Model/Item/ItemFactory.h"

#include "../../../includes/Model/Item/Ammo.h"
#include "../../../includes/Model/Item/Blood.h"
#include "../../../includes/Model/Item/Chest.h"
#include "../../../includes/Model/Item/Cross.h"
#include "../../../includes/Model/Item/Crown.h"
#include "../../../includes/Model/Item/Cup.h"
#include "../../../includes/Model/Item/Food.h"
#include "../../../includes/Model/Item/Key.h"
#include "../../../includes/Model/Item/Kit.h"

Item* ItemFactory::getItem(int itemTypeId, int uniqueId) {
  switch (itemTypeId) {
    case 6:
      return new Ammo(uniqueId);
      break;

    case 7:
      return new Blood(uniqueId);
      break;

    case 8:
      return new Chest(uniqueId);
      break;

    case 9:
      return new Cross(uniqueId);
      break;

    case 10:
      return new Crown(uniqueId);
      break;

    case 11:
      return new Cup(uniqueId);
      break;

    case 12:
      return new Food(uniqueId);
      break;

    case 13:
      return new Key(uniqueId);
      break;

    case 14:
      return new Kit(uniqueId);
      break;

    default:
      return nullptr;
      break;
  }
}