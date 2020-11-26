#include <iostream>

#include "../server/includes/Model/Game/Game.h"
#include "../server/includes/Model/Player/Player.h"
#include "../server/includes/Server/Server.h"
#include "CPPUnit.h"

Test(PlayerTakesDamageSuccesfully) {
  Player myPlayer(100, 2);

  TEST_ASSERT_EQUAL_INT(myPlayer.takeDamage(25), 75);
}

Test(PlayerTakesFatalDamageAndDies) {
  Player myPlayer(100, 2);

  TEST_ASSERT_EQUAL_INT(myPlayer.takeDamage(100), 0);
}

Test(PlayerDiesAndRespawnsWithFullLifeButIfKilledAgainItDoesnt) {
  Player myPlayer(100, 1);
  myPlayer.takeDamage(100);

  TEST_ASSERT_EQUAL_INT(myPlayer.getHealth(), 100);
  myPlayer.takeDamage(100);
  TEST_ASSERT_EQUAL_INT(myPlayer.getHealth(), 0);
}
int main() {
  RUN_TEST(PlayerTakesDamageSuccesfully);
  RUN_TEST(PlayerTakesFatalDamageAndDies);
  RUN_TEST(PlayerDiesAndRespawnsWithFullLifeButIfKilledAgainItDoesnt);

  TEST_PRINT_OVERALL();
}
