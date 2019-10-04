#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>

#include "map.h"
template<typename K, typename V>
class BstMap : public Map<K, V>
{
 private:
  class Node
  {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node(const K & key, const V & value) : key(key), value(value), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  BstMap() : root(NULL) {}

  Node * copy(Node * node) {
    if (node == NULL) {
      return node;
    }
    Node * newnode = new Node(node->key, node->value);
    if (node->left != NULL) {
      newnode->left = copy(node->left);
    }
    if (node->right != NULL) {
      newnode->right = copy(node->right);
    }
    return newnode;
  }
  BstMap<K, V> & operator=(const BstMap<K, V> & rhs) {
    if (this != &rhs) {
      destroy(root);
      root = copy(rhs.root);
    }
    return *this;
  }
  BstMap(const BstMap<K, V> & rhs) : root(NULL) { root = copy(rhs.root); }
  virtual void add(const K & key, const V & value) {
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
        (*current)->value = value;
        return;
      }
    }
    *current = new Node(key, value);
  }
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * current = root;

    while (current != NULL) {
      if (key < current->key) {
        current = current->left;
      }
      else if (key > current->key) {
        current = current->right;
      }
      else {
        return current->value;
      }
    }
    throw std::invalid_argument("Here lookup: Key not found.\n");
  }
  virtual void remove(const K & key) {
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
          (*current)->value = (*p)->value;
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
  virtual ~BstMap<K, V>() { destroy(root); }
};
