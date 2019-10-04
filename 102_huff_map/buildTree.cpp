#include <stdio.h>
#include <stdlib.h>

#include <cstdlib>
#include <iostream>

#include "node.h"
Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t pq;
  for (int i = 0; i < 257; i++) {
    if (counts[i] > 0) {  //>0?
      //Node * new_node = new Node(i, counts[i]);
      pq.push(new Node(i, counts[i]));
      // std::cout << "Now top sym is:" << pq.top()->sym << std::endl;
    }
  }
  while (pq.size() > 1) {
    Node * top1 = pq.top();
    pq.pop();

    Node * top2 = pq.top();
    pq.pop();

    Node * newtop = new Node(top1, top2);
    pq.push(newtop);
  }
  return pq.top();
}
