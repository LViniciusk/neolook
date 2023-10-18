#include <iostream>
using namespace std;
#include "OrderedList.h"

int main() {
    OrderedList<int> lista;
    for (int i = 100000; i > 0; i--) {
        lista.insert(i);
    }

    cout << lista.size() << endl;
}