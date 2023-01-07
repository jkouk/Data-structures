#include "../a_b/AB_tree.h"

int main() {
  AB_tree<int> ab(6, 2, 4);
  ab.insert(9);
  ab.insert(14);
  ab.insert(17);
  ab.insert(5);
  ab.print(ab.get_root());
  return 0;
}
