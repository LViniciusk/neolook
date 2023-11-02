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
#include <string>
#include <vector>

#include "System/System.h"
#include "TAD'S/PriorityQueue.h"
#include "TAD'S/Queue.h"

using namespace std;

int main() {
    int qPcs;
    string arq;
    bool politica;

    cout << "Digite a quantidade de computadores: ";
    cin >> qPcs;
    cout << "Digite o nome do arquivo: ";
    cin >> arq;
    cout << "Digite a politica de escalonamento (0 - FCFS, 1 - SJF): ";
    cin >> politica;
    System system(qPcs, arq, politica);

    return 0;
}