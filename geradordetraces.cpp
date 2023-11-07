#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

#include "TAD'S/PriorityQueue.h"

// ESTE ARQUIVO IMPLEMENTA A LÓGICA DE UM GERADOR DE TRACES

// Para executar: ./gerador <quantidade de processos> <nome do arquivo>

int main(int argc, char* argv[]) {
    int qProcessos = atoi(argv[1]);
    std::string nomeArquivo = argv[2];
    PriorityQueue<std::string> pq;
    std::ofstream out("testes/" + nomeArquivo);
    srand(time(NULL));
    for (int i = 0; i < qProcessos; i++) {
        int instante = rand() % ((int)qProcessos / 20);
        int d_cpu = rand() % 20;
        int d_disco = rand() % 20;
        int d_rede = rand() % 20;
        std::string s = "";
        s += std::to_string(instante);
        s += " ";
        s += std::to_string(d_cpu);
        s += " ";
        s += std::to_string(d_disco);
        s += " ";
        s += std::to_string(d_rede);
        pq.push(instante, s);
    }

    while (!pq.empty()) {
        out << pq.top() << std::endl;
        pq.pop();
    }

    out.close();
}