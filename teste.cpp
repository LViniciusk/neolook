#include <iostream>

#include "TAD'S/PriorityQueue.h"
#include "TAD'S/Queue.h"

int main() {
    PriorityQueue<int> pq;

    for (int i = 100; pq.size() < 10; i -= 2) {
        pq.push(i);
    }

    while (!pq.empty()) {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    std::cout << std::endl;

    Queue<int> q;

    for (int i = 100; q.size() < 10; i -= 2) {
        q.push(i);
    }

    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
}

// Saída: 82 84 86 88 90 92 94 96 98 100
//        100 98 96 94 92 90 88 86 84 82
