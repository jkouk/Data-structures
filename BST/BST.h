
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
  Node() {
    this->left = NULL;
    this->right = NULL;
  };
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
using namespace std;

template <typename T> Node<T>::Node(T value, Node *left, Node *right) {
  this->value = value;
  this->left = left;
  this->right = right;
}

template <typename T> Node<T> *Node<T>::get_left() { return this->left; }
template <typename T> Node<T> *Node<T>::get_right() { return this->right; }
template <typename T> T Node<T>::get_value() { return this->value; }
template <typename T> void Node<T>::set_left(Node<T> *node) {
  this->left = node;
}

template <typename T> bool is_left(Node<T> *child, Node<T> *parent) {
  if (parent->get_left() == child)
    return true;
  return false;
}
template <typename T> void Node<T>::set_right(Node<T> *node) {
  this->right = node;
}

template <typename T> void Node<T>::set_value(T value) { this->value = value; }

template <typename T> BST<T>::BST(T value) {
  this->root = new Node<T>(value, NULL, NULL);
}

// Find will return a vector with the node that it found and its parent. The
// second value will be used for inserting
template <typename T> vector<Node<T> *> BST<T>::find(T value) {
  Node<T> *curr_node = this->root, *parent = NULL;

  while (curr_node != NULL) {
    if (curr_node->get_value() == value)
      return {curr_node, parent};
    else {
      parent = curr_node;
      if (curr_node->get_value() > value)
        curr_node = curr_node->get_left();
      else
        curr_node = curr_node->get_right();
    }
  }
  return {NULL, parent};
}

template <typename T> Node<T> *BST<T>::insert(T value) {
  Node<T> *new_node = new Node<T>(value, NULL, NULL);
  vector<Node<T> *> nodes = this->find(value);

  auto iter = nodes.begin();

  if (*iter == NULL) {
    if (*(iter + 1) == NULL) {
      this->root = new_node;
    } else {
      if ((*(iter + 1))->get_value() > value)
        (*(iter + 1))->set_left(new_node);
      else
        (*(iter + 1))->set_right(new_node);
    }

    return new_node;
  }

  //  if the node was found return NULL
  return NULL;
}

template <typename T> bool BST<T>::remove(T value) {
  vector<Node<T> *> nodes = this->find(value);
  auto iter = nodes.begin();
  if (*iter == NULL) {
    cout << "Node not found" << endl;
    return false;
  }

  // If node has no right child delete immediately
  if ((*iter)->get_right() == NULL) {

    if (*iter == this->root) {
      this->root = (*iter)->get_left();
      return true;
    }

    if (is_left(*iter, (*(iter + 1))))
      (*(iter + 1))->set_left((*iter)->get_left());
    else
      (*(iter + 1))->set_right((*iter)->get_left());
    return true;
  }

  if ((*iter)->get_left() == NULL) {
    if (*iter == this->root) {
      this->root = (*iter)->get_right();
      return true;
    }
    if (is_left(*iter, (*(iter + 1))))
      (*(iter + 1))->set_left((*iter)->get_right());
    else
      (*(iter + 1))->set_right((*iter)->get_right());
    return true;
  }

  Node<T> *curr_node = (*iter)->get_right(), *parent = *iter;

  while (curr_node->get_left() != NULL) {
    parent = curr_node;
    curr_node = curr_node->get_left();
  }

  if (curr_node->get_right() == NULL) {
    if (is_left(curr_node, parent))
      (parent)->set_left(curr_node->get_left());
    else
      (parent)->set_right(NULL);
  }
  auto buff = (*iter)->get_value();
  (*iter)->set_value(curr_node->get_value());
  curr_node->set_value(buff);

  return true;
}

template <typename T> void BST<T>::pre_order(Node<T> *node) {

  if (this->root == NULL)
    return;
  cout << node->get_value();

  if (node->get_left() != NULL) {
    cout << ", ";
    this->pre_order(node->get_left());
  }
  if (node->get_right() != NULL) {
    cout << ", ";
    this->pre_order(node->get_right());
  }

  if (this->root == node)
    cout << endl;
}
template <typename T> void BST<T>::post_order(Node<T> *node) {
  if (this->root == NULL)
    return;

  if (node->get_left() != NULL) {
    this->post_order(node->get_left());
  }

  if (node->get_right() != NULL)
    this->post_order(node->get_right());

  cout << node->get_value();

  if (node == this->root)
    cout << endl;
  else
    cout << ", ";
}
template <typename T> Node<T> *BST<T>::get_root() { return this->root; }
template <typename T> void BST<T>::print(Node<T> *node) {
  if (this->root == NULL)
    return;

  cout << node->get_value();
  if (node->get_left() != NULL) {
    cout << " -- ";
    this->print(node->get_left());
  }
  if (node->get_right() != NULL) {

    cout << endl;
    cout << node->get_value() << " -- ";
    this->print(node->get_right());
  }
}
