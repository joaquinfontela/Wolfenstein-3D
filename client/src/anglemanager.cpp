#include "anglemanager.h"

AngleManager::AngleManager() {
  for (int i = 0; i <= this->ANGLE360; i++) {
    double radian = degreeToRadian(i, this->ANGLE180) + 0.0001;

    this->fSinTable[i] = sin(radian);
    this->fISinTable[i] = ((1.0) / this->fSinTable[i]);
    this->fCosTable[i] = cos(radian);
    this->fICosTable[i] = ((1.0) / this->fCosTable[i]);
    this->fTanTable[i] = tan(radian);
    this->fITanTable[i] = ((1.0) / this->fTanTable[i]);

    if (i >= this->ANGLE90 && i < this->ANGLE270) {
      this->fXStepTable[i] = (64.0) / this->fTanTable[i];
      if (this->fXStepTable[i] > 0)
        this->fXStepTable[i] = -this->fXStepTable[i];
    } else {
      this->fXStepTable[i] = (64.0) / this->fTanTable[i];
      if (this->fXStepTable[i] < 0)
        this->fXStepTable[i] = -this->fXStepTable[i];
    }

    if (i >= this->ANGLE0 && i < this->ANGLE180) {
      this->fYStepTable[i] = (64.0) * this->fTanTable[i];
      if (this->fYStepTable[i] < 0)
        this->fYStepTable[i] = -this->fYStepTable[i];
    } else {
      this->fYStepTable[i] = (64.0) * this->fTanTable[i];
      if (this->fYStepTable[i] > 0)
        this->fYStepTable[i] = -this->fYStepTable[i];
    }
  }

  for (int i = -this->ANGLE30; i <= this->ANGLE30; i++) {
    double radian = this->degreeToRadian(i, this->ANGLE180);
    this->fFishTable[i + this->ANGLE30] = (1.0/cos(radian));
  }
}

double AngleManager::fTan(int i) { return this->fTanTable[i]; }
double AngleManager::fITan(int i) { return this->fITanTable[i]; }
double AngleManager::fCos(int i) { return this->fCosTable[i]; }
double AngleManager::fICos(int i) { return this->fICosTable[i]; }
double AngleManager::fSin(int i) { return this->fSinTable[i]; }
double AngleManager::fISin(int i) { return this->fISinTable[i]; }
double AngleManager::fXStep(int i) { return this->fXStepTable[i]; }
double AngleManager::fYStep(int i) { return this->fYStepTable[i]; }
double AngleManager::degreeToRadian(double degree, int angle180) {
  return (degree * PI) / (angle180);
}
