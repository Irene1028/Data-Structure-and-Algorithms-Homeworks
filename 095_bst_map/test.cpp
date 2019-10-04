#include <cstdlib>
#include <iostream>

#include "bstmap.h"
#include "map.h"

int main(void) {
  BstMap<int, int> map;
  BstMap<int, int> map2;
  // using the answer of 091_traversals - 3
  map.add(2, 1);
  map.add(4, 2);
  map.add(1, 3);
  map.add(7, 4);
  map.add(3, 5);
  map.add(9, 6);
  map.add(-1, 7);
  map.add(88, 8);
  map.add(17, 9);
  map.add(-23, 10);
  map.add(16, 11);
  map.add(44, 12);
  map.add(77, 13);
  std::cout << "value of 1 is:" << map.lookup(1) << std::endl;
  std::cout << "value of 9 is:" << map.lookup(9) << std::endl;
  map.remove(2);
  map.remove(16);
  map.remove(-1);

  //  std::cout << "mid_order: " << std::endl;
  //map.inorder();
  std::cout << "value of -23 is:" << map.lookup(-23) << std::endl;
  std::cout << "value of 9 is:" << map.lookup(9) << std::endl;
  std::cout << "value of 17 is:" << map.lookup(17) << std::endl;
  map2 = map;
  std::cout << "value of -23 is:" << map.lookup(-23) << std::endl;
  std::cout << "value of 9 is:" << map.lookup(9) << std::endl;
  std::cout << "value of 17 is:" << map.lookup(17) << std::endl;

  return EXIT_SUCCESS;
}
