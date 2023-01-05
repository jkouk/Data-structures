#include "../AVL/AVL.h"

int main() {
  AVL<int> avl(6);
  avl.insert(9);
  avl.insert(14);
  avl.insert(17);
  avl.insert(5);
  avl.insert(7);
  avl.insert(16);
  avl.insert(20);
  avl.insert(18);
  avl.insert(19);
  avl.insert(4);
  avl.insert(11);
  avl.remove(6);
  avl.remove(9);
  avl.remove(14);
  avl.remove(4);
  avl.remove(5);
  avl.remove(20);
  avl.print(avl.get_root());
  cout << endl;
  return 0;
}
