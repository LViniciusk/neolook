#include <iostream>
using namespace std;
#include "OrderedList.h"
#include "PriorityQueue.cpp"
#include "Queue.cpp"

int main() {
    PriorityQueue pq;
    Queue<int> q;
    q.push(10);
    q.push(32);
    q.push(15);
    pq.insert(4);
    pq.insert(2);
    pq.insert(8);
    pq.insert(7);
    pq.insert(1);
    pq.insert(5);
    pq.insert(3);
    pq.insert(6);
    pq.insert(10);

    cout << "Queue: " << endl;
    while(!q.empty()){
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;

    cout << "Priority Queue: " << endl;
    pq.print();

    while (!pq.empty()) {
        cout << "Front: " << pq.front() << endl;
        pq.pop();
    }
}