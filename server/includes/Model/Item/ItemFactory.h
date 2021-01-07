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
  Item* getItem(int itemTypeId, int uniqueId);
};

#endif