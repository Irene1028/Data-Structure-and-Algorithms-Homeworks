#include "node.h"

#include <string>
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //WRITE ME!
  if (sym != NO_SYM) {
    assert((left == NULL) && (right == NULL));
    std::pair<unsigned, BitString> curpair(sym, b);
    theMap.insert(curpair);
    //theMap[sym] = b;
  }
  else {
    assert(left != NULL && right != NULL);
    //BitString b_left = b.plusZero();
    //BitString b_right = b.plusOne();
    left->buildMap(b.plusZero(), theMap);
    right->buildMap(b.plusOne(), theMap);
  }
}
