#include <iostream>
using namespace std;
#include "OrderedList.h"
#include "PriorityQueue.h"
#include "Queue.h"

int main() {
    PriorityQueue pq;
    pq.insert(4);
    pq.insert(2);
    pq.insert(8);
    pq.insert(7);
    pq.insert(1);
    pq.insert(5);
    pq.insert(3);
    pq.insert(6);
    pq.insert(10);

    cout << "Priority Queue: " << endl;
    pq.print();

    while (!pq.empty()) {
        cout << "Front: " << pq.front() << endl;
        pq.pop();
    }
}