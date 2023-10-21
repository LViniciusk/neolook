/**
 * @file main.cpp
 * @author Júnior Silva (junior.silva@alu.ufc.br) - 554222
 * @author Linyker Vinicius (botlink2030@alu.ufc.br) - 556280
 * @brief
 * @version 0.1
 * @date 20-10-2023
 *
 *
 */

#include <iostream>

#include "TAD'S/PriorityQueue.h"
#include "TAD'S/Queue.h"

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

    std::cout << "Queue: " << std::endl;
    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << std::endl;

    std::cout << "Priority Queue: " << std::endl;
    pq.print();

    while (!pq.empty()) {
        std::cout << "Front: " << pq.front() << std::endl;
        pq.pop();
    }
}