#include "BST.cpp"

int main() {
  BST<int> *bst = new BST<int>(6);
  bst->insert(6);
  bst->insert(9);
  bst->insert(14);
  bst->insert(17);
  bst->insert(5);
  bst->insert(7);
  bst->pre_order(bst->get_root());
  return 0;
}
