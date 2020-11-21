#include <iostream>
#include <queue>

template <class T>
class NullPtrQueue {
 private:
  std::queue<T> q;

 public:
  NullPtrQueue();
  ~NullPtrQueue();

  void push(T element);
  T pop();
  T front();
  bool isEmpty();
};

template <class T>
NullPtrQueue<T>::NullPtrQueue() {}

template <class T>
NullPtrQueue<T>::~NullPtrQueue() {}

template <class T>
void NullPtrQueue<T>::push(T element) {
  q.push(element);
}

template <class T>
T NullPtrQueue<T>::pop() {
  if (q.empty()) {
    return nullptr;
  }
  T elementToReturn = q.front();
  q.pop();
  return elementToReturn;
}

template <class T>
T NullPtrQueue<T>::front() {
  return q.front();
}

template <class T>
bool NullPtrQueue<T>::isEmpty() {
  return q.empty();
}
