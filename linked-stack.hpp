#include <iostream>
using namespace std;

#ifndef MAX
#define MAX 50
#endif

template <typename T>
struct Node {
  T info;
  Node<T> *prev, *next;
};

template <typename T>
struct Stack(Stack<T> &s) {
    Node <T> *begin, *end;
};

template <typename T>
void initialize(Stack<T> &s) {
    s.begin = NULL;
    s.end = NULL;
};

template <typename T>
bool full(Stack<T> &s) {
    return false;
}

template <typename T>
bool empty(Stack<T> &s) {
    return (s.end == NULL) ? true : false;
}

template <typename T>
bool push(Stack<T> &s, T element) {
    Node<T> *n = new Node<T>;
    if (n == NULL) return false;
    n->info = element;
    n->prev = NULL;
    n->next = NULL;
    
    if (s.begin == NULL) {
        s.begin = n;
        s.end = n;
    }
    else {
        s.end->next = n;
        n->prev = s.end;
        s.end = n;
    }
    return true;
}

template <typename T>
bool pop(Stack<T> &s, T &value) {
    if (empty(s)) return false;
    
    Node<T> *n = s.end;
    if (n == NULL) return false;
    value = n->info;

    if (n == s.begin && n == s.end) {
        s.begin = NULL;
        s.end = NULL;
    }
    else {
        s.end = n->prev;
        s.end->next = NULL;
    }
    delete n;
    return true;
}

template <typename T>
bool top(Stack<T> &s, T &value) {
    if (empty(s)) return false
    value = s.end->info;
    return true;
}
