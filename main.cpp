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

    cout << "Digite a quantidade de computadores: ";
    cin >> qPcs;
    cout << "Digite o nome do arquivo: ";
    cin >> arq;

    System<Queue<Process>> s(qPcs, arq);

    return 0;
}