#include <iostream>
#include <deque>
// #include <algorithm>
// #include <iostream>
// #include <string>
#include <stdlib.h>

using namespace std;

void test1(void* item)
{
    item = (void*) malloc(sizeof(int));
    // item = (int*)666;
}

int main()
{
  // std::deque<int> deq;
  //
  // deq.push_front(1);
  // // deq.push_front(2);
  // // deq.push_front(3);
  // // deq.push_front(4);
  // // deq.push_front(5);
  // // deq.push_front(6);
  // size_t st = 0;
  // st = -1;
  // printf("%zd\n", st);

  // cout << deq[0] << endl;
  // cout << deq[deq.size() - 1] << endl;
  //
  // cout << deq[5] << endl;

  // cout << deq.max_size() << endl;
  // cout << deq.size() << endl;

  void* item = NULL;
  test1(&item);

  // cout << *((int*)item) << endl;
  cout << item << endl;

}
