#include <iostream>
using namespace std;
#include "OrderedList.h"
#include "PriorityQueue.h"
#include "Queue.h"

int main() {
    PriorityQueue<int> pq;
    int n = 10;
    while (n--) {
        pq.push(n);
    }

    for (int i = 0; i < 10; i++) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
}