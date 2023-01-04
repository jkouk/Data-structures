
#ifndef BST_H
#define BST_H

#include <cstddef>
#include <exception>
#include <ios>
#include <iostream>
#include <vector>

// Define the basic part of the tree : The node

template <typename T> class Node {
private:
  T value;
  Node *left;
  Node *right;

public:
  Node(T value, Node *left, Node *right);
  Node<T> *get_left();
  Node<T> *get_right();
  void set_left(Node<T> *node);
  void set_right(Node<T> *node);
  T get_value();
  void set_value(T value);
};

template <typename T> class BST {
private:
  Node<T> *root;

public:
  // Constructor gets a value to add as root
  BST(T value);
  Node<T> *insert(T value);
  bool remove(T value);
  std ::vector<Node<T> *> find(T value);
  Node<T> *get_root();
  void pre_order(Node<T> *node);
  void post_order(Node<T> *node);
  // Gets as input the node we want to start from
  void print(Node<T> *node);
};

#endif
