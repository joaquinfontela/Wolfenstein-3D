#include "InstantUseItem.h"

class Treasure : public InstantUseItem {
 public:
  void use(Player player) override;
};