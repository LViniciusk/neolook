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
    PriorityQueue<int> pq;
    pq.push(2);
    pq.push(3);
    pq.push(1);
    while (!pq.empty()) {
        std::cout << pq.top() << " ";
        pq.pop();
    }
}