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
#include <stdlib.h>

#include "TAD'S/PriorityQueue.h"
#include "TAD'S/Queue.h"
#include "System/Computer.h"
#include "System/Process.h"










using namespace std;

int main() {

    int N = 10;
    Queue<Process> p;



    p.push(Process(10, 20, 30));

    Computer<Queue<int>> pcs[N];

    for(int i  = 0; i < N; i++ ){
        pcs[i].CPU.push(p.front().d_cpu);
    }

    srand (48);


    for(int i = 0; i < N; i++) cout << "PC " << i << ": " << pcs[i].CPU.front() << endl;

}