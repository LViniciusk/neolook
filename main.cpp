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

#include <time.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "System/Computer.h"
#include "System/Process.h"
#include "TAD'S/PriorityQueue.h"
#include "TAD'S/Queue.h"

using namespace std;

void print(Queue<Process> p) {
    int t = p.size();
    for (int i = 0; i < t; i++) {
        cout << "Processo " << i << ":" << endl;
        cout << endl;
        cout << "Start: " << p.front().d_start << endl;
        cout << "CPU: " << p.front().d_cpu << endl;
        cout << "DISK: " << p.front().d_disk << endl;
        cout << "REDE: " << p.front().d_rede << endl;
        cout << endl;
        p.pop();
    }
}

void readTrace(Queue<Process> &p) {
    FILE *trace;
    int d_start, d_cpu, d_disk, d_rede;
    trace = fopen("trace.txt", "r");
    while (fscanf(trace, "%d %d %d %d", &d_start, &d_cpu, &d_disk, &d_rede) ==
           4) {
        p.push(Process(d_start, d_cpu, d_disk, d_rede));
    }
    fclose(trace);
}

int main() {
    srand(time(0));
    Queue<Process> p;
    int op, n{5};

    cout << "Politica: ";
    cin >> op;

    if (op == 0) {
        Computer<PriorityQueue<int>> *pcs = new Computer<PriorityQueue<int>>[n];
        readTrace(p);

        cout << "Quantia de processos pendentes: " << p.size() << "\n\n";
        cout << "Distribuindo . . ." << endl;
        int t = p.size();
        for (int i = 0; i < t; i++) {
            pcs[rand() % n].receiveProcess(p.front());
            p.pop();
        }

        cout << "Quantia de processos pendentes: " << p.size() << "\n\n";

        for (int i = 0; i < n; i++) {
            cout << "PC " << i << ": "
                 << "\n";
            pcs[i].print();
        }

        print(p);
    } else {
        Computer<Queue<int>> *pcs = new Computer<Queue<int>>[n];
        readTrace(p);

        cout << "Quantia de processos pendentes: " << p.size() << "\n\n";
        cout << "Distribuindo . . ." << endl;
        int t = p.size();
        for (int i = 0; i < t; i++) {
            pcs[rand() % n].receiveProcess(p.front());
            p.pop();
        }

        cout << "Quantia de processos pendentes: " << p.size() << "\n\n";

        for (int i = 0; i < n; i++) {
            cout << "PC " << i << ": "
                 << "\n";
            pcs[i].print();
        }

        print(p);
    }
}