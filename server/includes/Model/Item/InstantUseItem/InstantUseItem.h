#include "../../Player/Player.h"
#include "../Item.h"

class InstantUseItem : public Item {
 public:
  virtual void use(Player player) = 0;
};