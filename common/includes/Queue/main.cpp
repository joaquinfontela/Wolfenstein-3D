#include "NullPtrQueue.h"

int main() {
  NullPtrQueue<int*> q;
  int five = 5;
  int six = 6;
  int eight = 8;
  q.push(&five);
  q.push(&six);
  q.push(&eight);
  for (int i = 0; i <= 4; i++) {
    if (q.front()) {
      std::cout << *(q.pop()) << std::endl;
      continue;
    }
    std::cout << "NULL\n";
  }

  return 0;
}