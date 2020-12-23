#include <algorithm>
#include <charconv>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <vector>

using namespace std;

struct node {
  int prev, next;
};
template <int N> struct mylist {
  using value_type = node;
  mylist() : store{N} {
    store[0].prev = store[0].next = 0;
  }
  void insert(int c) {
    auto& n = store[c] = {store[0].prev, 0};
    store[n.prev].next = c;
    store[n.next].prev = c;
  }
  vector<node> store;
};

int main(int argc, char** argv) {

  string line;
  getline(cin, line);
  mylist<1000000> numbers;
  for (int a = 0; a < line.size(); ++a) {
    int i = line[a] - '0' - 1;
    numbers.insert(i);
  }

  for (int i = 9; i < 1000000; ++i) {
    numbers.store[i] = {i - 1, i + 1};
  }
  numbers.store[0].prev = 999999;
  numbers.store[5].next = 9;
  numbers.store[9].prev = 5;
  numbers.store[999999].next = 0;

  int currentval = 0;
  for (int i = 0; i < 10000000; ++i) {
	int next1val = numbers.store[currentval].next;
    node* next1 = &numbers.store[next1val];
	int next2val = next1->next;
    node* next2 = &numbers.store[next2val];
	int next3val = next2->next;
    node* next3 = &numbers.store[next3val];
    int destination = currentval - 1;
    if (destination == -1)
      destination = 999999;
    while ((destination == next1val) || (destination == next2val) || (destination == next3val)) {
      destination = destination - 1;
      if (destination == -1)
        destination = 999999;
    }
    numbers.store[next1->prev].next = next3->next;
    numbers.store[next3->next].prev = exchange(next1->prev, destination);
    int destafter = exchange(numbers.store[destination].next, next1val);
    next3->next = destafter;
    numbers.store[destafter].prev = next3val;
    currentval = numbers.store[currentval].next;
  }
  node* oneIter = &numbers.store[0];
  int next1 = oneIter->next;
  int next2 = numbers.store[oneIter->next].next;

  cout << long(next1 + 1) * long(next2 + 1) << '\n';

  return 0;
}

