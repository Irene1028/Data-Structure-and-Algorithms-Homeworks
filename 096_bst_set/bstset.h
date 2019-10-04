#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>

#include "set.h"

template<typename T>
class BstSet : public Set<T>
{
 private:
  class Node
  {
   public:
    T key;
    Node * left;
    Node * right;
    Node(const T & key) : key(key), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  BstSet() : root(NULL) {}

  Node * copy(Node * node) {
    if (node == NULL) {
      return node;
    }
    Node * newnode = new Node(node->key);
    if (node->left != NULL) {
      newnode->left = copy(node->left);
    }
    if (node->right != NULL) {
      newnode->right = copy(node->right);
    }
    return newnode;
  }
  BstSet<T> & operator=(const BstSet<T> & rhs) {
    if (this != &rhs) {
      destroy(root);
      root = copy(rhs.root);
    }
    return *this;
  }
  BstSet(const BstSet<T> & rhs) : root(NULL) { root = copy(rhs.root); }
  virtual void add(const T & key) {
    //V ans = lookUp(key, value);
    Node ** current = &root;
    while ((*current) != NULL) {
      if (key < (*current)->key) {
        current = &(*current)->left;
      }
      else if (key > (*current)->key) {
        current = &(*current)->right;
      }
      else {
        std::cout << "this node existed\n";
        return;
      }
    }
    *current = new Node(key);
  }
  virtual bool contains(const T & key) const {
    Node * current = root;

    while (current != NULL) {
      if (key < current->key) {
        current = current->left;
      }
      else if (key > current->key) {
        current = current->right;
      }
      else {
        return true;
      }
    }
    return false;
  }
  virtual void remove(const T & key) {
    Node ** current = &root;
    while ((*current) != NULL) {
      if (key < (*current)->key) {
        current = &(*current)->left;
      }
      else if (key > (*current)->key) {
        current = &(*current)->right;
      }
      else {
        if ((*current)->left == NULL && (*current)->right == NULL) {  //current == leaf
          delete *current;
          *current = NULL;
          return;
        }
        else if ((*current)->left == NULL) {  //current have right but no left
          Node * temp = (*current)->right;
          delete *current;
          *current = temp;
          return;
        }
        else if ((*current)->right == NULL) {  //current have left but no right
          Node * temp = (*current)->left;
          delete *current;
          *current = temp;
          return;
        }
        else {
          Node ** p = &(*current)->right;
          while ((*p)->left != NULL) {
            p = &(*p)->left;
          }
          Node * temp_right = (*p)->right;
          (*current)->key = (*p)->key;
          delete *p;
          *p = temp_right;
          return;
        }
      }
    }
    throw std::invalid_argument("Here remove: Key not found.\n");
  }
  void destroy(Node * n) {
    if (n != NULL) {
      destroy(n->left);
      destroy(n->right);
      delete n;
    }
  }
  virtual ~BstSet<T>() { destroy(root); }
};
