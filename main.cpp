#include <iostream>
using namespace std;
#include "OrderedList.h"
#include "Queue.h"

int main() {
    Queue<int> q;
    OrderedList<int> lst;

    for (int i = 10; i >= 1; i--) {
        q.push(i);
        lst.insert(i);
    }

    for (auto& x : q) {
        cout << x << " ";
    }
    cout << endl;

    for (auto& x : lst) {
        cout << x << " ";
    }
}