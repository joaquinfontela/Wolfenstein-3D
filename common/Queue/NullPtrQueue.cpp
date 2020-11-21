#include "NullPtrQueue.h"

NullPtrQueue::NullPtrQueue() {}

NullPtrQueue::~NullPtrQueue() {}

void NullPtrQueue::push(int* element) { q.push(element); }

int* NullPtrQueue::pop() {
  if (q.empty()) {
    return nullptr;
  }
  int* elementToReturn = q.front();
  q.pop();
  return elementToReturn;
}

int* NullPtrQueue::front() { return q.front(); }

bool NullPtrQueue::isEmpty() { return q.empty(); }
