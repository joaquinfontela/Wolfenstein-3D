#include <iostream>

#include "../server/includes/Model/Game/Game.h"
#include "../server/includes/Model/Player/Player.h"
#include "../server/includes/Server/Server.h"
#include "../common/includes/Socket/SocketException.h"
#include "../common/includes/Socket/SocketCommunication.h"
#include "CPPUnit.h"

Test(SocketThrowsExcepctedException){

  SocketCommunication socket(-1);
  socket.connect("localhost", "8080");
}

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

  TestSuit playerTests("Player Test");
  playerTests.addTest(PlayerTakesDamageSuccesfully);
  playerTests.addTest(PlayerTakesFatalDamageAndDies);
  playerTests.addTest(PlayerDiesAndRespawnsWithFullLifeButIfKilledAgainItDoesnt);
  playerTests.run();


  TEST_ASSERT_THROWS(SocketThrowsExcepctedException, SocketException);
  TEST_PRINT_OVERALL();
}
