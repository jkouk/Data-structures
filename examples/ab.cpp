#include "../a_b/AB_tree.h"

int main() {
  AB_tree<int> ab(6, 2, 4);
  ab.insert(9);
  ab.insert(14);
  ab.insert(17);
  ab.insert(5);
  ab.insert(7);
  ab.insert(16);
  ab.insert(20);
  ab.insert(18);
  ab.insert(19);
  ab.insert(4);
  ab.insert(11);
  ab.print(ab.get_root());
  return 0;
}
