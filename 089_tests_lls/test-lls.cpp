#include <assert.h>

#include <cstdlib>

#include "il.h"

//testList
void testList() {
  //test default constructor
  IntList List1;
  assert(List1.size == 0 && List1.head == NULL && List1.tail == NULL);

  /*test copy constructor*/
  //
  IntList List2;
  List2.addFront(2);
  List2.addBack(6);
  List2.addBack(8);
  List2.addBack(3);
  //testcase: [2,6,8,3]
  IntList List3(List2);
  assert(List2.head != List3.head);
  assert(List2.tail != List3.tail);
  assert(List2.getSize() == List3.getSize());
  for (int i = 0; i < List2.getSize(); i++) {
    assert(List2[i] == List3[i]);
  }

  /*test addFront()*/
  //
  //when List2 is not empty

  List2.addFront(100);  //List2:[100,2,6,8,3]
  assert(List2.head->data == 100 && List2.getSize() == 5);
  //when a new List4 is empty
  IntList List4;
  List4.addFront(100);  //List4:[100]
  assert(List4.getSize() == 1 && List4[0] == 100 && List4.head != NULL && List4.tail != NULL);

  /*test addBack()*/
  //
  //when List2 is not empty
  List2.addBack(90);  //List2:[100,2,6,8,3,90]
  assert(List2.getSize() == 6 && List2.tail->data == 90);
  //when a new List5 is empty
  IntList List5;
  List5.addBack(33);
  assert(List5.getSize() == 1 && List5.head->data == 33 && List5.tail->data == 33);

  /*test remove()*/
  //
  //remove the first one of List2:[100,2,6,8,3,90]
  //List2:[2,6,8,3,90]
  assert(List2.remove(100) == 1 && List2.getSize() == 5 && List2.head->prev == NULL);

  //remove the last one in List2:[2,6,8,3,90]
  //List2:[2,6,8,3]
  assert(List2.remove(90) == 1 && List2.getSize() == 4 && List2.tail->next == NULL);

  //remove a middle element in List2:[2,6,8,3]
  //List2:[2,8,3]
  assert(List2.remove(6) == 1 && List2.getSize() == 3 && List2.head->next->data == 8);

  //remove a value not in List2:[2,8,3]
  assert(List2.remove(14) == 0 && List2.find(14) == -1 && List2.getSize() == 3);

  //remove the only value in List5:[33]
  List5.remove(33);
  assert(List5.getSize() == 0 && List5.head == NULL && List5.tail == NULL);
  assert(List5.remove(2) == 0);

  /*test operator=*/
  //List2:[2,8,3]
  IntList List6;
  List6 = List2;
  assert(List6.head != List2.head && List6.getSize() == List2.getSize());
  for (int i = 0; i < List6.size; i++) {
    assert(List6[i] == List2[i]);
  }

  /*test operator[]*/
  assert(List2[0] == 2 && List2[2] == 3);

  /*test find()*/
  //
  //when List2:[2,8,3]is not empty
  assert(List2.find(2) == 0 && List2.find(8) == 1 && List2.find(5) == -1);
  //when List5 is empty
  assert(List5.find(3) == -1);
}

int main(void) {
  testList();
  return EXIT_SUCCESS;
}
