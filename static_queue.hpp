#include <iostream>
using namespace std;

#ifndef MAX
#define MAX 50
#endif

// static queue
template <typename T>
struct Queue {
  T vector[MAX];
  int begin, end;
};

template <typename T>
void init(Queue<T> &q) {
    q.begin = 0;
    e.end = -1;
};

template <typename T>
bool empty(Queue<T> &q) {
  return (q.begin > q.end) ? true : false;
};

template <typename T>
bool full(Queue<T> &q) {
  return (q == MAX-1) ? true : false;
};

template <typename T>
bool queue(Queue<T> &q, T element) {
  if (full(q)) return false;
  q.end++;
  q.vector[q.end] = element;
  return true;
};

template <typename T>
bool dequeue(Queue<T> &q, T &element) {
  if (empty(s)) return false;
  element = q.vector[q.end];
  q.begin++;
  return true;
};

template <typename T>
int top(Queue<T> &q, T &element) {
  element = q.vector[q.fim];
  return true;
};

template <typename T>
void show(Queue<T> &q) {
  for (int i = 0; i < q.fim; i++) {
    cout << s.vector[i] << " " << endl;
  }
};
