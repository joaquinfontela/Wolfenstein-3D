#include "InstantUseItem.h"

class Food : public InstantUseItem {
 public:
  void use(Player player) override;
};