#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE
template<typename T>
class LinkedList
{
 private:
  class Node
  {
   public:
    T data;
    Node * next;
    Node * prev;
    Node(T data) : data(data), next(NULL), prev(NULL) {}
  };
  Node * head;
  Node * tail;
  int size;
  //size?
 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    for (Node * p = rhs.head; p != NULL; p = p->next) {
      addBack(p->data);
    }
  }
  LinkedList & operator=(const LinkedList & rhs);
  ~LinkedList() {
    Node * next;
    for (Node * p = head; p != NULL; p = next) {
      next = p->next;
      delete p;
    }
  }
  void addFront(const T & item);
  void addBack(const T & item);
  bool remove(const T & item);
  T & operator[](int index);
  const T & operator[](int index) const;
  int find(const T & item) const;
  int getSize() const { return size; }
};

template<typename T>
void LinkedList<T>::addBack(const T & item) {
  Node * pnode = new Node(item);
  if (getSize() == 0) {
    tail = pnode;
    head = pnode;
  }
  else {
    pnode->prev = tail;
    tail->next = pnode;
    tail = pnode;
  }
  size++;
}

template<typename T>
void LinkedList<T>::addFront(const T & item) {
  Node * pnode = new Node(item);
  if (getSize() == 0) {
    tail = pnode;
    head = pnode;
  }
  else {
    pnode->next = head;
    head->prev = pnode;
    head = pnode;
  }
  size++;
}

template<typename T>
bool LinkedList<T>::remove(const T & item) {
  int sizetmp = size;
  for (Node * p = head; p != NULL; p = p->next) {
    if (p->data == item) {
      //remove middle element
      if (p->prev != NULL && p->next != NULL) {
        Node * temp_prev = p->prev;
        Node * temp_next = p->next;
        delete p;
        temp_prev->next = temp_next;
        temp_next->prev = temp_prev;
      }
      else if (p->prev == NULL && p->next != NULL) {
        //remove the first element
        //Node * temp_prev = head;
        Node * temp_next = p->next;
        delete p;
        head = temp_next;
        temp_next->prev = NULL;
      }
      else if (p->next == NULL && p->prev != NULL) {
        //remove the last element
        Node * temp_prev = p->prev;
        //Node * temp_next = tail;
        delete p;
        tail = temp_prev;
        temp_prev->next = NULL;
      }
      size--;
      break;
    }
  }
  if (sizetmp > size)
    return 1;
  else
    return 0;
}

template<typename T>
int LinkedList<T>::find(const T & item) const {
  int count = 0;
  for (Node * p = head; p != NULL; p = p->next) {
    if (p->data == item) {
      return count;
    }
    else {
      count++;
    }
  }
  return -1;
}

template<typename T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList & rhs) {
  Node * next;
  for (Node * p = head; p != NULL; p = next) {
    next = p->next;
    delete p;
  }
  head = NULL;
  tail = NULL;
  size = 0;
  for (Node * p = rhs.head; p != NULL; p = p->next) {
    addBack(p->data);
  }
  return *this;
}

template<typename T>
T & LinkedList<T>::operator[](int index) {
  assert(index >= 0);
  Node * p;
  for (p = head; p != NULL && index > 0; p = p->next) {
    index = index - 1;
  }
  assert(p != NULL);
  return p->data;
}

template<typename T>
const T & LinkedList<T>::operator[](int index) const {
  assert(index >= 0);
  Node * p;
  for (p = head; p != NULL && index > 0; p = p->next) {
    index = index - 1;
  }
  assert(p != NULL);

  return p->data;
}
#endif
