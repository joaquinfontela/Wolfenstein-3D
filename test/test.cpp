#include <iostream>

#include "../common/includes/Socket/SocketCommunication.h"
#include "../common/includes/Socket/SocketException.h"
#include "../server/includes/Model/Game/Game.h"
#include "../server/includes/Model/Item/Blood.h"
#include "../server/includes/Model/Item/Chest.h"
#include "../server/includes/Model/Item/Cross.h"
#include "../server/includes/Model/Item/Crown.h"
#include "../server/includes/Model/Item/Cup.h"
#include "../server/includes/Model/Item/Food.h"
#include "../server/includes/Model/Item/ItemDrop/ItemDrop.h"
#include "../server/includes/Model/Item/Key.h"
#include "../server/includes/Model/Item/MedKit.h"
#include "../server/includes/Model/Player/Player.h"
#include "../server/includes/Server/Server.h"
#include "CPPUnit.h"

Test(SocketThrowsExcepctedException) {
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

Test(PlayerWith10PointsOfHealthPicksUpBloodAndGetsOnePointOfHealth) {
  Player myPlayer(10, 1);
  Blood blood;
  ItemDrop bloodDrop(blood);

  TEST_ASSERT_TRUE(bloodDrop.pickUpIfPossible(myPlayer));
  TEST_ASSERT_EQUAL_INT(myPlayer.getHealth(), 11);
}

Test(PlayerWith11PointsOfHealthCannotPickUpBloodAndDoesNotGetExtraHealth) {
  Player myPlayer(11, 1);
  Blood blood;
  ItemDrop bloodDrop(blood);

  TEST_ASSERT_FALSE(bloodDrop.pickUpIfPossible(myPlayer));
  TEST_ASSERT_EQUAL_INT(myPlayer.getHealth(), 11);
}

Test(PlayerPicksUpChestAndGets100Points) {
  Player myPlayer(100, 1);
  Chest myChest;
  ItemDrop chestDrop(myChest);
  chestDrop.pickUpIfPossible(myPlayer);

  TEST_ASSERT_EQUAL_INT(myPlayer.getScore(), 100);
}

Test(PlayerPicksUpCrossAndGets10Points) {
  Player myPlayer(100, 1);
  Cross myCross;
  ItemDrop crossDrop(myCross);
  crossDrop.pickUpIfPossible(myPlayer);

  TEST_ASSERT_EQUAL_INT(myPlayer.getScore(), 10);
}

Test(PlayerPicksUpCupAndGets50Points) {
  Player myPlayer(100, 1);
  Cup myCup;
  ItemDrop cupDrop(myCup);
  cupDrop.pickUpIfPossible(myPlayer);

  TEST_ASSERT_EQUAL_INT(myPlayer.getScore(), 50);
}

Test(PlayerPicksUpCrownAndGets200Points) {
  Player myPlayer(100, 1);
  Crown myCrown;
  ItemDrop crownDrop(myCrown);
  crownDrop.pickUpIfPossible(myPlayer);

  TEST_ASSERT_EQUAL_INT(myPlayer.getScore(), 200);
}

Test(PlayerPicksUpFoodAndGets10OfHealth) {
  Player myPlayer(50, 1);
  Food myFood;
  ItemDrop foodDrop(myFood);
  foodDrop.pickUpIfPossible(myPlayer);

  TEST_ASSERT_EQUAL_INT(myPlayer.getHealth(), 60);
}

Test(PlayerCannotPickUpFoodWhenHeHas100PointsOfHealth) {
  Player myPlayer(100, 1);
  Food myFood;
  ItemDrop foodDrop(myFood);
  TEST_ASSERT_FALSE(foodDrop.pickUpIfPossible(myPlayer));
  TEST_ASSERT_EQUAL_INT(myPlayer.getHealth(), 100);
}

Test(PlayerPicksUpMedKitAndGets20OfHealth) {
  Player myPlayer(50, 1);
  MedKit medKit;
  ItemDrop medKitDrop(medKit);
  medKitDrop.pickUpIfPossible(myPlayer);

  TEST_ASSERT_EQUAL_INT(myPlayer.getHealth(), 70);
}

Test(PlayerCannotPickUpMedKitWhenHeHas100PointsOfHealth) {
  Player myPlayer(100, 1);
  MedKit myMedKit;
  ItemDrop medKitDrop(myMedKit);
  TEST_ASSERT_FALSE(medKitDrop.pickUpIfPossible(myPlayer));
  TEST_ASSERT_EQUAL_INT(myPlayer.getHealth(), 100);
}

Test(PlayerHasNotKeyBeforePickingItUpAndWhenHePicksItUpHeHasAKey) {
  Player myPlayer(100, 1);
  Key myKey;
  ItemDrop keyDrop(myKey);

  TEST_ASSERT_EQUAL_INT(myPlayer.hasKey(), 0);
  keyDrop.pickUpIfPossible(myPlayer);
  TEST_ASSERT_EQUAL_INT(myPlayer.hasKey(), 1);
}

int main() {
  TestSuit playerTests("Player Test");
  playerTests.addTest(PlayerTakesDamageSuccesfully);
  playerTests.addTest(PlayerTakesFatalDamageAndDies);
  playerTests.addTest(
      PlayerDiesAndRespawnsWithFullLifeButIfKilledAgainItDoesnt);

  playerTests.addTest(
      PlayerWith10PointsOfHealthPicksUpBloodAndGetsOnePointOfHealth);
  playerTests.addTest(
      PlayerWith11PointsOfHealthCannotPickUpBloodAndDoesNotGetExtraHealth);
  playerTests.addTest(PlayerPicksUpChestAndGets100Points);
  playerTests.addTest(PlayerPicksUpCrossAndGets10Points);
  playerTests.addTest(PlayerPicksUpCupAndGets50Points);
  playerTests.addTest(PlayerPicksUpCrownAndGets200Points);
  playerTests.addTest(PlayerPicksUpFoodAndGets10OfHealth);
  playerTests.addTest(PlayerCannotPickUpFoodWhenHeHas100PointsOfHealth);
  playerTests.addTest(PlayerPicksUpMedKitAndGets20OfHealth);
  playerTests.addTest(PlayerCannotPickUpMedKitWhenHeHas100PointsOfHealth);
  playerTests.addTest(
      PlayerHasNotKeyBeforePickingItUpAndWhenHePicksItUpHeHasAKey);

  playerTests.run();

  TEST_ASSERT_THROWS(SocketThrowsExcepctedException, SocketException);
  TEST_PRINT_OVERALL();
}
