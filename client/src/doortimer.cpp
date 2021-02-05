#include "../includes/doortimer.h"

void DoorTimer::run() {
  int rate = 1000 / 30;
  int rest = 0;
  int behind = 0;
  int lost = 0;
  auto t1 = std::chrono::steady_clock::now();
  auto t2 = t1;
  std::chrono::duration<float, std::milli> diff = t2 - t1;
  while (this->alive) {
    this->matrix.updateTimers(abs(diff.count() / 20));
    auto t1 = std::chrono::steady_clock::now();
    auto t2 = t1;
    t2 = std::chrono::steady_clock::now();
    diff = t2 - t1;
    t1 = t2;
    rest = rate - ceil(diff.count());
    if (rest < 0) {
      behind -= rest;
      lost = rate + (behind - behind % rate);
      rest = rate - behind % rate;
      t1 += std::chrono::milliseconds(lost);
      std::this_thread::sleep_for(std::chrono::milliseconds(rest));
      t1 += std::chrono::milliseconds(rate);
    }
  }
}
