#ifndef SYSTEM_H
#define SYSTEM_H

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "../TAD'S/PriorityQueue.h"
#include "../TAD'S/Queue.h"
#include "Computer.h"
#include "Network.h"
#include "Process.h"

#define SEED 12345678

template <typename Type>
class System {
   private:
    int qPcs;                   // quantidade de computadores
    Computer<Type>* computers;  // computadores do sistema
    Network<Type> network;      // rede do sistema

   public:
    System(int qPcs, std::string arq) {
        this->qPcs = qPcs;
        computers = new Computer<Type>[qPcs];
        network = Network<Type>();
        loadFile(arq);
    }

    void loadFile(std::string arq) {
        Queue<Process> p;  // fila auxiliar, para carregar o arquivo

        std::cout << "Carregando arquivo " << arq << "..." << std::endl;
        std::ifstream file(arq);
        if (!file.is_open()) throw std::runtime_error("Erro ao abrir arquivo");

        int instant, d_cpu, d_disk, d_rede;
        while (file >> instant >> d_cpu >> d_disk >> d_rede) {
            Process process(instant, d_cpu, d_disk, d_rede);
            p.push(process);
        }

        file.close();
        std::cout << "Arquivo carregado com sucesso" << std::endl;

        // Distribui os processos para os computadores aleatoriamente
        srand(SEED);
        while (!p.empty()) {
            int i = rand() % qPcs;
            computers[i].receiveProcess(p.front());
            p.pop();
        }

        // Imprime o estado inicial do sistema
        std::cout << "Estado inicial do sistema: " << std::endl;
        for (int i = 0; i < qPcs; i++) {
            std::cout << "Computador " << i << std::endl;
            std::cout << "\tFila de processos: " << std::endl;
            for (auto& process : computers[i].processos) process.print();
            std::cout << "----------------------------------------"
                      << std::endl;
            std::cout << std::endl;
        }
    }

    void printPCS() {
        for (int i = 0; i < qPcs; i++) {
            std::cout << "Computador " << i << std::endl;
            computers[i].print();
            std::cout << std::endl;
            std::cout << "----------------------------------------"
                      << std::endl;
        }
    }

    ~System() { delete[] computers; }
};

#endif  // SYSTEM_H