#include "../../../includes/Model/Door/UnlockableDoor.h"

UnlockableDoor::UnlockableDoor() : Door() {}

bool UnlockableDoor::isLocked() { return false; }