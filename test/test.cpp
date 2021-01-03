#include <iostream>
#include <cstring>
#include <math.h>

#include "../common/includes/Socket/SocketCommunication.h"
#include "../common/includes/Socket/SocketWrapper.h"
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
#include "../server/includes/Model/Map/Map.h"
#include "CPPUnit.h"

#define PRECISION 100000.0
#define EPSILON 10.0/PRECISION

Map map(24, 24);

Test(SocketThrowsExcepctedException) {
  SocketCommunication socket(-1);
  socket.connect("localhost", "8080");
}

Test(PlayerTakesDamageSuccesfully) {
  Player myPlayer(100, 2);

  TEST_ASSERT_EQUAL_INT(myPlayer.takeDamage(25, map), 75);
}

Test(PlayerTakesFatalDamageAndDies) {
  Player myPlayer(100, 2);

  TEST_ASSERT_EQUAL_INT(myPlayer.takeDamage(100, map), 0);
}

Test(PlayerDiesAndRespawnsWithFullLifeButIfKilledAgainItDoesnt) {
  Player myPlayer(100, 1);
  myPlayer.takeDamage(100, map);

  TEST_ASSERT_EQUAL_INT(myPlayer.getHealth(), 100);
  myPlayer.takeDamage(100, map);
  TEST_ASSERT_EQUAL_INT(myPlayer.getHealth(), 0);
}

Test(PlayerWith10PointsOfHealthPicksUpBloodAndGetsOnePointOfHealth) {
  Player myPlayer(10, 1);
  Blood blood;
  ItemDrop bloodDrop(&blood);

  TEST_ASSERT_TRUE(bloodDrop.pickUpIfPossible(myPlayer));
  TEST_ASSERT_EQUAL_INT(myPlayer.getHealth(), 11);
}

Test(PlayerWith11PointsOfHealthCannotPickUpBloodAndDoesNotGetExtraHealth) {
  Player myPlayer(11, 1);
  Blood blood;
  ItemDrop bloodDrop(&blood);

  TEST_ASSERT_FALSE(bloodDrop.pickUpIfPossible(myPlayer));
  TEST_ASSERT_EQUAL_INT(myPlayer.getHealth(), 11);
}

Test(PlayerPicksUpChestAndGets100Points) {
  Player myPlayer(100, 1);
  Chest myChest;
  ItemDrop chestDrop(&myChest);
  chestDrop.pickUpIfPossible(myPlayer);

  TEST_ASSERT_EQUAL_INT(myPlayer.getScore(), 100);
}

Test(PlayerPicksUpCrossAndGets10Points) {
  Player myPlayer(100, 1);
  Cross myCross;
  ItemDrop crossDrop(&myCross);
  crossDrop.pickUpIfPossible(myPlayer);

  TEST_ASSERT_EQUAL_INT(myPlayer.getScore(), 10);
}

Test(PlayerPicksUpCupAndGets50Points) {
  Player myPlayer(100, 1);
  Cup myCup;
  ItemDrop cupDrop(&myCup);
  cupDrop.pickUpIfPossible(myPlayer);

  TEST_ASSERT_EQUAL_INT(myPlayer.getScore(), 50);
}

Test(PlayerPicksUpCrownAndGets200Points) {
  Player myPlayer(100, 1);
  Crown myCrown;
  ItemDrop crownDrop(&myCrown);
  crownDrop.pickUpIfPossible(myPlayer);

  TEST_ASSERT_EQUAL_INT(myPlayer.getScore(), 200);
}

Test(PlayerPicksUpFoodAndGets10OfHealth) {
  Player myPlayer(50, 1);
  Food myFood;
  ItemDrop foodDrop(&myFood);
  foodDrop.pickUpIfPossible(myPlayer);

  TEST_ASSERT_EQUAL_INT(myPlayer.getHealth(), 60);
}

Test(PlayerCannotPickUpFoodWhenHeHas100PointsOfHealth) {
  Player myPlayer(100, 1);
  Food myFood;
  ItemDrop foodDrop(&myFood);
  TEST_ASSERT_FALSE(foodDrop.pickUpIfPossible(myPlayer));
  TEST_ASSERT_EQUAL_INT(myPlayer.getHealth(), 100);
}

Test(PlayerPicksUpMedKitAndGets20OfHealth) {
  Player myPlayer(50, 1);
  MedKit medKit;
  ItemDrop medKitDrop(&medKit);
  medKitDrop.pickUpIfPossible(myPlayer);

  TEST_ASSERT_EQUAL_INT(myPlayer.getHealth(), 70);
}

Test(PlayerCannotPickUpMedKitWhenHeHas100PointsOfHealth) {
  Player myPlayer(100, 1);
  MedKit myMedKit;
  ItemDrop medKitDrop(&myMedKit);
  TEST_ASSERT_FALSE(medKitDrop.pickUpIfPossible(myPlayer));
  TEST_ASSERT_EQUAL_INT(myPlayer.getHealth(), 100);
}

Test(PlayerCannotSurpass100PointsOfHealth) {
  Player myPlayer(90, 1);
  MedKit myMedKit;
  ItemDrop medKitDrop(&myMedKit);
  TEST_ASSERT_TRUE(medKitDrop.pickUpIfPossible(myPlayer));
  TEST_ASSERT_EQUAL_INT(myPlayer.getHealth(), 100);
}

Test(PlayerHasNotKeyBeforePickingItUpAndWhenHePicksItUpHeHasAKey) {
  Player myPlayer(100, 1);
  Key myKey;
  ItemDrop keyDrop(&myKey);

  TEST_ASSERT_EQUAL_INT(myPlayer.hasKey(), 0);
  keyDrop.pickUpIfPossible(myPlayer);
  TEST_ASSERT_EQUAL_INT(myPlayer.hasKey(), 1);
}

Test(sendDoubles1) {
  double value = 10000000.5;
  uint32_t firstMessage = (uint32_t)value;
  uint32_t secondMessage = (value - (int) value) * PRECISION;
  double ans = firstMessage + (((double)secondMessage) / PRECISION);
  TEST_ASSERT_TRUE(value == ans);
}

Test(sendDoubles2) {
  double value = 10000000.12345;
  uint32_t firstMessage = (uint32_t)value;
  uint32_t secondMessage = (long int)((value - (int) value) * PRECISION);
  double ans = firstMessage + (((double)secondMessage) / PRECISION);
  TEST_ASSERT_TRUE(value < ans + EPSILON && value > ans - EPSILON);
}

Test(sendDoubles3) {
  double value = 1999463499.1999345;
  uint32_t firstMessage = (uint32_t)value;
  uint32_t secondMessage = (long int)((value - (int) value) * PRECISION);
  double ans = firstMessage + (((double)secondMessage) / PRECISION);
  printf("\nDouble: %lX, ans: %lX as hexa\n", (uint64_t)value, (uint64_t)ans);
  printf("Double: %f, asn: %f as doubles\n\n", value, ans);
  TEST_ASSERT_TRUE(value < ans + EPSILON && value > ans - EPSILON);
}

int main() {
  TestSuit playerTests("Player Test");
  TestSuit socketWrapperTest("Socket Wrapper Test");
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
  playerTests.addTest(PlayerCannotSurpass100PointsOfHealth);
  playerTests.addTest(
      PlayerHasNotKeyBeforePickingItUpAndWhenHePicksItUpHeHasAKey);
  socketWrapperTest.addTest(sendDoubles1);
  socketWrapperTest.addTest(sendDoubles2);
  socketWrapperTest.addTest(sendDoubles3);

  playerTests.run();
  socketWrapperTest.run();

  TEST_ASSERT_THROWS(SocketThrowsExcepctedException, SocketException);
  TEST_PRINT_OVERALL();
}
