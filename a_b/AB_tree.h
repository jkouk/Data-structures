#include <cstddef>
#include <iostream>
#include <iterator>
#include <list>
#include <ostream>

template <typename T> class AB_Node {
private:
  std::list<T> values;
  std::list<AB_Node<T> *> children;

public:
  AB_Node(T value);
  AB_Node() {}
  AB_Node<T> get_child(int position);
  void insert(T value, AB_Node<T> *left, AB_Node<T> *right, int a, int b);

  // Returns the position if the value was found, else returns -1
  AB_Node<T> *find(T value);
  void remove(T value);
  void add_left_child(AB_Node<T> *left) { this->children.push_front(left); }
  void add_right_child(AB_Node<T> *right) { this->children.push_back(right); }
  void push_value(T value) { this->values.push_back(value); }
  void set_left(AB_Node<T> *left) {
    this->children.erase(this->children.begin());
    add_left_child(left);
  }
  void set_right(AB_Node<T> *right) {
    this->children.erase((++this->children.rbegin()).base());
    add_right_child(right);
  }

  // Returns NULL if no new node was created else returns this node
  AB_Node<T> *rebalance(AB_Node<T> *parent, int a, int b);
  void print() {
    std::cout << "{ ";

    for (auto iter = this->values.begin(); iter != values.end(); ++iter) {
      std::cout << *iter;

      if (iter != --values.end())
        std::cout << ", ";
    }

    std::cout << " }" << std::endl;
    for (auto iter = this->children.begin(); iter != children.end(); ++iter) {
      if (*iter != NULL)
        (*iter)->print();
    }
  }
};

template <typename T> AB_Node<T>::AB_Node(T value) {
  values.push_back(value);
  children.push_back(NULL);
  children.push_back(NULL);
}

template <typename T> AB_Node<T> *AB_Node<T>::find(T value) {
  auto iter = (values.begin()), child_iter = ++(children.begin());
  T pos_1 = *iter;

  if (pos_1 > value) {
    if (*(children.rbegin()) != NULL)
      return *(children.begin());
    else
      return this;
  }
  while (1) {
    pos_1 = *iter;

    // Returns same node if the value was found
    if (pos_1 == value) {
      return NULL;
    }

    if (pos_1 < value) {
      if (*child_iter != NULL)
        return *child_iter;
      else
        return this;
    }

    ++iter;
    child_iter++;
  }
}

template <typename T> AB_Node<T> AB_Node<T>::get_child(int position) {
  int counter = 0;

  for (auto iter = children.begin(); iter != children.end(); ++iter) {
    if (counter == position)
      return *iter;
  }

  return NULL;
};

template <typename T>
void AB_Node<T>::insert(T value, AB_Node<T> *left, AB_Node<T> *right, int a,
                        int b) {

  auto iter = this->values.begin(), child_iter = this->children.begin();
  T pos_1;

  if (*iter > value) {
    values.push_front(value);

    if (right != NULL)
      children.push_front(right);
    children.push_front(left);
  }

  else {
    while (1) {

      pos_1 = *iter;

      if (pos_1 == value) {
        std::cout << "Value found" << std::endl;
        return;
      }
      ++iter;

      if (iter == values.end())
        break;
      T pos_2 = *iter;

      if (pos_2 > value) {

        values.insert(iter, value);

        if (right != NULL)
          children.insert(child_iter, right);
        children.insert(child_iter, left);
        return;
      }
      ++child_iter;
      ++child_iter;
    }

    if (pos_1 < value) {
      values.push_back(value);

      if (left != NULL)
        children.push_back(left);
      children.push_back(right);
    }
  }
}

template <typename T>
AB_Node<T> *AB_Node<T>::rebalance(AB_Node<T> *parent, int a, int b) {
  if ((int)children.size() < a || (int)children.size() > b) {
    int counter = 0;
    auto child_iter = this->children.begin(), iter = this->values.begin();

    T split_value;

    AB_Node<T> *left_child = new AB_Node<T>(), *right_child = NULL;

    // Find the (b+1)/2 value and break the node
    while (iter != values.end()) {
      if (counter == (b + 1) / 2 - 1) {

        split_value = (*iter);
        child_iter++;
        ++iter;
        break;
      }

      left_child->push_value(*iter);
      left_child->add_right_child(*child_iter);
      std::advance(child_iter, 1);
      left_child->add_right_child(*child_iter);
      std::advance(child_iter, 1);
      iter++;
      counter++;
    }

    if (iter != values.end())
      right_child = new AB_Node<T>();

    while (iter != values.end()) {
      right_child->push_value(*iter);
      right_child->add_right_child(*child_iter);
      std::advance(child_iter, 1);
      iter++;
    }
    child_iter++;
    right_child->add_right_child(*child_iter);

    if (parent == NULL) {
      AB_Node<T> *new_parent = new AB_Node<T>(split_value);
      new_parent->set_left(left_child);
      new_parent->set_right(right_child);
      return new_parent;
    } else {
      parent->insert(split_value, left_child, right_child, a, b);
    }
  }
  return NULL;
}

template <typename T> class AB_tree {
private:
  AB_Node<T> *root;
  int a;
  int b;

public:
  AB_tree(T value, int a, int b) {
    this->root = new AB_Node<T>(value);
    this->a = a;
    this->b = b;
  }
  AB_Node<T> *find(T value, AB_Node<T> *curr_node, bool print = true);
  void insert(T value);
  AB_Node<T> *get_root() { return this->root; }
  void print(AB_Node<T> *node) { node->print(); }
};

template <typename T>
AB_Node<T> *AB_tree<T>::find(T value, AB_Node<T> *curr_node, bool print) {
  auto last_node = curr_node;

  while (last_node != NULL) {
    last_node = curr_node->find(value);

    if (last_node == curr_node) {
      if (print)
        std::cout << "Node found" << std::endl;
      return NULL;
    }

    curr_node = last_node;
  }

  if (print)
    std::cout << "Node not found" << std::endl;
  return curr_node;
}

template <typename T> void AB_tree<T>::insert(T value) {
  AB_Node<T> *curr_node = this->root;
  auto last_node = curr_node;
  std::list<AB_Node<T> *> parents = {NULL};

  while (1) {
    last_node = curr_node->find(value);

    if (last_node == NULL) {
      std::cout << "Value exists" << std::endl;
      return;
    }

    if (last_node == curr_node) {
      break;
    }

    parents.push_back(curr_node);
    curr_node = last_node;
  }

  curr_node->insert(value, NULL, NULL, this->a, this->b);

  while (parents.size() != 0) {
    curr_node = curr_node->rebalance((*parents.rbegin()), this->a, this->b);

    if (parents.size() == 1 && curr_node != NULL)
      this->root = curr_node;
    curr_node = *parents.rbegin();
    parents.pop_back();
  }
}
