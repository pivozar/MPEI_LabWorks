#include <iostream>
#include "bidirectional_list.h"
#include "queue.h"

void TestBdList();
void BdListTask4();

void TestQueue();

int main(int argc, char* argv[]) {
    //TestBdList();
    //BdListTask4();
    //TestQueue();
    return 0;
}

void TestBdList() {
    BidirectionalList<int> list;
    std::cin >> list;
    BidirectionalList<int> list2 = list;
    BidirectionalList<int> list3(5);
    list3.PushFront(4);
    std::cout << list.PopFront() << std::endl;
    std::cout << list.Front() << " - " << list.Back() << std::endl;
    std::cout << list3 << std::endl;
    auto it = list2.Find(3);
    std::cout << *it;
}

void BdListTask4() {
    BidirectionalList<int> list;
    std::cin >> list;
    int given_num, list_max = list.Front();
    std::cin >> given_num;
    for (int & i : list) {
        if (i > list_max) {
            list_max = i;
        }
    }
    if (list_max > given_num) {
        std::cout << "Before:\n" << list << '\n';
        BidirectionalList<int> list_copy = list;
        for (int & i : list_copy) {
            if (!(i&1)) {
                list.Erase(list.Find(i));
            }
        }
        std::cout << "After:\n" << list << '\n';
    }
}

void TestQueue() {
    Queue<int> q1;
    std::cin >> q1;
    std::cout << q1 << '\n';
    Queue<int> q2 = q1;
    for (int i=0; i<50; ++i) {
        q1.Push(i);
    }
    std::cout << q1 << '\n';
    for (int i=0; i<50; ++i) {
        q1.Pop();
    }
    std::cout << q1 << '\n';
    for (int i=0; i<50; ++i) {
        q2.Push(i);
        q2.Pop();
    }
    std::cout << q2 << '\n';
}