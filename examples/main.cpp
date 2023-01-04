#include "../BST/BST.cpp"

int main() {
  BST<int> *bst = new BST<int>(6);
  bst->insert(6);
  bst->insert(9);
  bst->insert(14);
  bst->insert(17);
  bst->insert(5);
  bst->insert(7);
  bst->insert(16);
  bst->insert(20);
  bst->insert(18);
  bst->insert(19);
  bst->insert(4);
  bst->insert(11);
  bst->remove(6);
  bst->remove(9);
  bst->remove(14);
  bst->remove(4);
  bst->remove(5);
  bst->remove(20);
  bst->print(bst->get_root());
  return 0;
}
