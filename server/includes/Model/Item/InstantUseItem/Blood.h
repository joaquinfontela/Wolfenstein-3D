#include "InstantUseItem.h"

class Blood : public InstantUseItem {
 public:
  void use(Player player) override;
};