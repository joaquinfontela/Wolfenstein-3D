#include <math.h>

#include <cstring>
#include <iostream>

#include "../common/includes/Socket/SocketCommunication.h"
#include "../common/includes/Socket/SocketException.h"
#include "../common/includes/Socket/SocketWrapper.h"
#include "../server/includes/Model/Game/Game.h"
#include "../server/includes/Model/Item/Blood.h"
#include "../server/includes/Model/Item/Key.h"
#include "../server/includes/Model/Item/Kit.h"
#include "../server/includes/Model/Map/Map.h"
#include "../server/includes/Model/Player/Player.h"
#include "../server/includes/Server/Server.h"
#include "CPPUnit.h"

#define PRECISION 100000.0
#define EPSILON 10.0 / PRECISION

Map map(24, 24);

// PLAYER TEST
// *********************************************************************
Test(SocketThrowsExcepctedException) {
  SocketCommunication socket(-1);
  socket.connect("localhost", "8080");
}

//****************************************************************************
// Double Wrapper Test
Test(sendDoubles1) {
  double value = 10000000.5;
  uint32_t firstMessage = (uint32_t)value;
  uint32_t secondMessage = (value - (int)value) * PRECISION;
  double ans = firstMessage + (((double)secondMessage) / PRECISION);
  TEST_ASSERT_TRUE(value == ans);
}

Test(sendDoubles2) {
  double value = 10000000.12345;
  uint32_t firstMessage = (uint32_t)value;
  uint32_t secondMessage = (long int)((value - (int)value) * PRECISION);
  double ans = firstMessage + (((double)secondMessage) / PRECISION);
  TEST_ASSERT_TRUE(value < ans + EPSILON && value > ans - EPSILON);
}

Test(sendDoubles3) {
  double value = 1999463499.1999345;
  uint32_t firstMessage = (uint32_t)value;
  uint32_t secondMessage = (long int)((value - (int)value) * PRECISION);
  double ans = firstMessage + (((double)secondMessage) / PRECISION);
  printf("\nDouble: %lX, ans: %lX as hexa\n", (uint64_t)value, (uint64_t)ans);
  printf("Double: %f, asn: %f as doubles\n\n", value, ans);
  TEST_ASSERT_TRUE(value < ans + EPSILON && value > ans - EPSILON);
}
//*****************************************************************************

int main() {
  TestSuit playerTests("Player Test");
  TestSuit socketWrapperTest("Socket Wrapper Test");

  socketWrapperTest.addTest(sendDoubles1);
  socketWrapperTest.addTest(sendDoubles2);
  socketWrapperTest.addTest(sendDoubles3);

  playerTests.run();
  socketWrapperTest.run();

  TEST_ASSERT_THROWS(SocketThrowsExcepctedException, SocketException);
  TEST_PRINT_OVERALL();
}
