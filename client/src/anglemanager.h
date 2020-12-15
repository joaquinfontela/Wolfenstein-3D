#ifndef ANGLEMANAGER_H_
#define ANGLEMANAGER_H_

#include <math.h>

#define HEIGHT 600
#define WIDTH 800
#define PI 3.14159265359

class AngleManager {
 public:
  int ANGLE60 = WIDTH;
  int ANGLE30 = floor(ANGLE60 / 2);
  int ANGLE15 = floor(ANGLE30 / 2);
  int ANGLE90 = floor(ANGLE30 * 3);
  int ANGLE180 = floor(ANGLE90 * 2);
  int ANGLE270 = floor(ANGLE90 * 3);
  int ANGLE360 = floor(ANGLE60 * 6);
  int ANGLE0 = 0;
  int ANGLE5 = floor(ANGLE30 / 6);
  int ANGLE2 = floor(ANGLE30 / 15);
  int ANGLE1 = floor(ANGLE2 / 2);
  int ANGLE1p5 = floor(ANGLE1 * 3 / 2);
  int ANGLE10 = floor(ANGLE5 * 2);
  int ANGLE45 = floor(ANGLE15 * 3);

  double fSinTable[(WIDTH * 6) + 1];
  double fISinTable[(WIDTH * 6) + 1];
  double fCosTable[(WIDTH * 6) + 1];
  double fICosTable[(WIDTH * 6) + 1];
  double fTanTable[(WIDTH * 6) + 1];
  double fITanTable[(WIDTH * 6) + 1];
  double fFishTable[(WIDTH * 6) + 1];
  double fXStepTable[(WIDTH * 6) + 1];
  double fYStepTable[(WIDTH * 6) + 1];

  AngleManager();
  double fTan(int i);
  double fITan(int i);
  double fCos(int i);
  double fICos(int i);
  double fSin(int i);
  double fISin(int i);
  double fXStep(int i);
  double fYStep(int i);
  double degreeToRadian(double degree, int angle180);
};

#endif  // ANGLEMANAGER_H_
