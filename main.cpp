#include <iostream>
using namespace std;
#include "OrderedList.h"
#include "Queue.h"

int main() {
    Queue<int> lista;
    for (int i = 10; i > 0; i--) {
        lista.push(i);
    }

    cout << "Tamanho: " << lista.size() << "\n\n" << "Elementos: \n";
    int aux = lista.size();
    for (int i = 0; i < aux; i++) {
        cout << lista.front() << endl;
        lista.pop();
    }

}