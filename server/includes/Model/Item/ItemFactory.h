#ifndef ITEM_FACTORY_H
#define ITEM_FACTORY_H

#include "../../../../common/includes/YAML/YAMLConfigReader.h"
#include "Item.h"

class ItemFactory {
 private:
  YAMLConfigReader yamlConfigReader;

 public:
  ItemFactory();
  ItemFactory(std::string& configFileName);

  /*
   * @brief [SERVER-SIDE] Receives an itemTypeId and returns the corresponding
   * item with id uniqueId.
   *
   * @param itemTypeId integer that represents a item type.
   *
   * @param uniqueId integer that differentiates an item from any other one.
   *
   * @return a dynamic pointer to a item if itemTypeId is valid, nullptr
   * otherwise.
   */
  Item* getItem(int itemTypeId, int uniqueId);
};

#endif