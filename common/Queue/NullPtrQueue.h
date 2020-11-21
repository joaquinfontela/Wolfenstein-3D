#include <iostream>
#include <queue>

class NullPtrQueue {
 private:
  std::queue<int*> q;

 public:
  NullPtrQueue();
  ~NullPtrQueue();

  void push(int* element);
  int* pop();
  int* front();
  bool isEmpty();
};
