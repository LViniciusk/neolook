/**
 * @file main.cpp
 * @author Júnior Silva (junior.silva@alu.ufc.br)
 * @author Linyker Vinicius (botlink2030@alu.ufc.br)
 * @brief
 * @version 0.1
 * @date 20-10-2023
 *
 *
 */

#include <iostream>
using namespace std;
#include "TAD'S/PriorityQueue.cpp"
#include "TAD'S/Queue.cpp"

int main() {
    PriorityQueue<char> pq;
    Queue<int> q;
    q.push(10);
    q.push(32);
    q.push(15);
    // pq.insert(4);
    // pq.insert(2);
    // pq.insert(8);
    // pq.insert(7);
    // pq.insert(1);
    // pq.insert(5);
    // pq.insert(3);
    // pq.insert(6);
    // pq.insert(10);
    pq.insert('a');
    pq.insert('z');
    pq.insert('r');
    pq.insert('g');
    pq.insert('i');

    cout << "Queue: " << endl;
    while (!q.empty()) {
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