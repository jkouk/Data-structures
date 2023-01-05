#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>

using namespace std;

template <typename T> class AVL_Node {
private:
  int height;
  int value;
  AVL_Node<T> *left;
  AVL_Node<T> *right;

public:
  AVL_Node(T value, AVL_Node<T> *left, AVL_Node<T> *right) {
    this->value = value;
    this->left = left;
    this->right = right;
    this->height = 1;
  };
  void increase_height();
  void insert(T value, AVL_Node<T> *node = NULL);
  vector<int> get_child_heights();
  int get_height();
  void set_value(T value) { this->value = value; }
  AVL_Node<T> *l_rot(AVL_Node<T> *parent);
  AVL_Node<T> *r_rot(AVL_Node<T> *parent);
  AVL_Node<T> *rl_rot(AVL_Node<T> *parent);
  AVL_Node<T> *lr_rot(AVL_Node<T> *parent);
  AVL_Node<T> *get_left();
  AVL_Node<T> *get_right();
  void set_left(AVL_Node<T> *node);
  void set_right(AVL_Node<T> *node);
  T get_value();
};

template <typename T> class AVL {
private:
  AVL_Node<T> *root;

public:
  AVL(T value);
  void insert(T value, AVL_Node<T> *node = NULL);
  void remove(T value);
  vector<AVL_Node<T> *> find(T value);
  AVL_Node<T> *get_root() { return this->root; }
  void pre_order(AVL_Node<T> *node);
  void post_order(AVL_Node<T> *node);
  // Gets as input the node we want to start from
  void print(AVL_Node<T> *node);
  void set_root(AVL_Node<T> *node) { this->root = node; }
};
template <typename T> T AVL_Node<T>::get_value() { return this->value; }
template <typename T> bool is_left(AVL_Node<T> *child, AVL_Node<T> *parent) {

  if (parent->get_left() == child)
    return true;
  return false;
}

template <typename T> AVL_Node<T> *AVL_Node<T>::get_left() {
  return this->left;
}
template <typename T> AVL_Node<T> *AVL_Node<T>::get_right() {
  return this->right;
}
template <typename T> void AVL_Node<T>::set_left(AVL_Node<T> *node) {
  this->left = node;
}

template <typename T> void AVL_Node<T>::set_right(AVL_Node<T> *node) {
  this->right = node;
}

template <typename T> void AVL_Node<T>::increase_height() {
  int left_height = this->get_child_heights().at(0),
      right_height = this->get_child_heights().at(1);

  this->height = max(left_height, right_height) + 1;
}

template <typename T> AVL_Node<T> *AVL_Node<T>::l_rot(AVL_Node<T> *parent) {
  AVL_Node<T> *right_child = this->get_right();
  AVL_Node<T> *rl_child = right_child->get_left();

  right_child->set_left(this);
  this->set_right(rl_child);

  if (parent != NULL) {
    if (is_left(this, parent))
      parent->set_left(right_child);
    else
      parent->set_right(right_child);
  }
  this->increase_height();
  right_child->increase_height();

  return right_child;
}
template <typename T> AVL_Node<T> *AVL_Node<T>::r_rot(AVL_Node<T> *parent) {
  AVL_Node<T> *left_child = this->get_left();
  AVL_Node<T> *lr_child = left_child->get_right();

  left_child->set_right(this);
  this->set_left(lr_child);

  if (is_left(this, parent))
    parent->set_left(left_child);
  else
    parent->set_right(left_child);

  this->increase_height();
  left_child->increase_height();

  return left_child;
}
template <typename T> AVL_Node<T> *AVL_Node<T>::rl_rot(AVL_Node<T> *parent) {

  (this->get_right())->r_rot(this);
  return ((this)->l_rot(parent));
}

template <typename T> AVL_Node<T> *AVL_Node<T>::lr_rot(AVL_Node<T> *parent) {

  (this->get_left())->l_rot(this);
  return ((this)->r_rot(parent));
}
template <typename T> int AVL_Node<T>::get_height() { return this->height; }

template <typename T> vector<int> AVL_Node<T>::get_child_heights() {
  int left_height = 0, right_height = 0;

  if (this->get_left() != NULL) {
    left_height = (this->get_left())->get_height();
  }

  if (this->get_right() != NULL)
    right_height = (this->get_right())->get_height();

  return {left_height, right_height};
}

template <typename T> AVL<T>::AVL(T value) {
  this->root = new AVL_Node<T>(value, NULL, NULL);
}

template <typename T> void AVL<T>::insert(T value, AVL_Node<T> *node) {
  // The path that was followed to find the position
  vector<AVL_Node<T> *> path = {NULL};

  if (node == NULL)
    node = this->root;

  while (1) {
    if (value < node->get_value()) {
      if (node->get_left() == NULL) {
        node->set_left(new AVL_Node<T>(value, NULL, NULL));
        path.push_back(node);
        break;
      } else {
        path.push_back(node);
        node = node->get_left();
      }
    } else {
      if (value > node->get_value()) {
        if (node->get_right() == NULL) {
          node->set_right(new AVL_Node<T>(value, NULL, NULL));
          path.push_back(node);
          break;
        } else {
          path.push_back(node);
          node = node->get_right();
        }

      } else {
        cout << "Node already found" << endl;
        return;
      }
    }
  }
  for (auto iter = path.rbegin(); *iter != NULL; ++iter) {
    (*iter)->increase_height();
    int left_height = (*iter)->get_child_heights().at(0),
        right_height = (*iter)->get_child_heights().at(1);
    // Right-right grandchildren height and right-left
    int rr_height = 0, rl_height = 0, lr_height = 0, ll_height = 0;
    if ((*iter)->get_right() != NULL) {
      if ((*iter)->get_right()->get_right() != NULL)
        rr_height = (*iter)->get_right()->get_right()->get_height();
      if ((*iter)->get_right()->get_left() != NULL)
        rl_height = (*iter)->get_right()->get_left()->get_height();
    }
    if ((*iter)->get_left() != NULL) {
      if ((*iter)->get_left()->get_right() != NULL)
        lr_height = (*iter)->get_left()->get_right()->get_height();
      if ((*iter)->get_left()->get_left() != NULL)
        ll_height = (*iter)->get_left()->get_left()->get_height();
    }

    if (rr_height == left_height + 1) {
      AVL_Node<T> *top_n = (*iter)->l_rot(*(iter + 1));

      if (*(iter + 1) == NULL)
        this->root = top_n;

      continue;
    }
    if (ll_height == right_height + 1) {
      AVL_Node<T> *top_n = (*iter)->r_rot(*(iter + 1));

      if (*(iter + 1) == NULL)
        this->root = top_n;

      continue;
    }
    if (rl_height == left_height + 1) {
      AVL_Node<T> *top_n = (*iter)->rl_rot(*(iter + 1));

      if (*(iter + 1) == NULL)
        this->root = top_n;

      continue;
    }
    if (lr_height == right_height + 1) {
      AVL_Node<T> *top_n = (*iter)->lr_rot(*(iter + 1));

      if (*(iter + 1) == NULL)
        this->root = top_n;

      continue;
    }
  }
}

template <typename T> vector<AVL_Node<T> *> AVL<T>::find(T value) {
  AVL_Node<T> *curr_node = this->root, parent = NULL;

  while (1) {

    if (curr_node == NULL) {
      cout << "Value not found" << endl;
      break;
    } else {
      if (curr_node->get_value() < value)
        curr_node = curr_node->get_right();
      else {
        if (curr_node->get_value() > value)
          curr_node = curr_node->get_left();
        else {
          cout << "Value found" << endl;
          break;
        }
      }
    }
    parent = curr_node;
  }

  return {curr_node, parent};
}

template <typename T> void AVL<T>::remove(T value) {
  vector<AVL_Node<T> *> path = {NULL};
  AVL_Node<T> *curr_node = this->root;

  while (curr_node != NULL) {
    if (curr_node->get_value() < value) {
      path.push_back(curr_node);
      curr_node = curr_node->get_right();
    }

    else {
      if (curr_node->get_value() > value) {
        path.push_back(curr_node);
        curr_node = curr_node->get_left();
      }

      else
        break;
    }
  }

  AVL_Node<T> *del_node = curr_node;

  if (curr_node->get_right() == NULL) {
    if ((*(path.rbegin()) != NULL)) {
      if (is_left(curr_node, *(path.rbegin())))
        (*(path.rbegin()))->set_left(curr_node->get_left());
      else
        (*(path.rbegin()))->set_right(curr_node->get_left());
    }
  }

  else {
    path.push_back(curr_node);

    curr_node = curr_node->get_right();

    while (1) {
      if (curr_node->get_left() == NULL) {
        del_node->set_value(curr_node->get_value());
        break;
      }
      path.push_back(curr_node);
      curr_node = curr_node->get_left();
    }

    if (is_left(curr_node, *(path.rbegin())))
      (*(path.rbegin()))->set_left(NULL);
    else
      (*(path.rbegin()))->set_right(NULL);
  }
  for (auto iter = path.rbegin(); *iter != NULL; ++iter) {
    (*iter)->increase_height();
    int left_height = (*iter)->get_child_heights().at(0),
        right_height = (*iter)->get_child_heights().at(1);
    // Right-right grandchildren height and right-left
    int rr_height = 0, rl_height = 0, lr_height = 0, ll_height = 0;
    if ((*iter)->get_right() != NULL) {
      if ((*iter)->get_right()->get_right() != NULL)
        rr_height = (*iter)->get_right()->get_right()->get_height();
      if ((*iter)->get_right()->get_left() != NULL)
        rl_height = (*iter)->get_right()->get_left()->get_height();
    }
    if ((*iter)->get_left() != NULL) {
      if ((*iter)->get_left()->get_right() != NULL)
        lr_height = (*iter)->get_left()->get_right()->get_height();
      if ((*iter)->get_left()->get_left() != NULL)
        ll_height = (*iter)->get_left()->get_left()->get_height();
    }

    if (rr_height == left_height + 1) {
      AVL_Node<T> *top_n = (*iter)->l_rot(*(iter + 1));

      if (*(iter + 1) == NULL)
        this->root = top_n;

      continue;
    }
    if (ll_height == right_height + 1) {
      AVL_Node<T> *top_n = (*iter)->r_rot(*(iter + 1));

      if (*(iter + 1) == NULL)
        this->root = top_n;

      continue;
    }
    if (rl_height == left_height + 1) {
      AVL_Node<T> *top_n = (*iter)->rl_rot(*(iter + 1));

      if (*(iter + 1) == NULL)
        this->root = top_n;

      continue;
    }
    if (lr_height == right_height + 1) {
      AVL_Node<T> *top_n = (*iter)->lr_rot(*(iter + 1));

      if (*(iter + 1) == NULL)
        this->root = top_n;

      continue;
    }
  }
}

template <typename T> void AVL<T>::print(AVL_Node<T> *node) {
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
