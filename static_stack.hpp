#include <iostream>
using namespace std;

#ifndef MAX
#define MAX 50
#endif

// static stack
template <typename T>
struct Stack {
  T vector[MAX];
  int top;
};

template <typename T>
void init(Stack<T> &s) {
    s.top = -1;
};

template <typename T>
bool isEmpty(Stack<T> &s) {
  return (s.top == -1) ? true : false;
};

template <typename T>
bool isFull(Stack<T> &s) {
  return (s.top == MAX) ? true : false;
};

template <typename T>
void push(Stack<T> &s, T element) {
  if (isFull(s)) return;
  s.top++;
  s.vector[s.top] = element;
};

template <typename T>
void pop(Stack<T> &s) {
  if (isEmpty(s)) return;
  s.top--;
};

template <typename T>
int top(Stack<T> &s) {
  return s.vector[s.top];
};

template <typename T>
void show(Stack<T> &s) {
  for (int i = 0; i <= s.top; i++) {
    cout << s.vector[i] << " " << endl;
  }
};
