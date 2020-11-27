#include "InstantUseItem.h"

class MedKit : public InstantUseItem {
 public:
  void use(Player player) override;
};