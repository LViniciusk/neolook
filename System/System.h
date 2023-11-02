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

class System {
   private:
    int qPcs;             // quantidade de computadores
    Computer* computers;  // computadores do sistema
    Network* network;     // rede do sistema
    bool politica;        // politica de escalonamento

   public:
    /**
     * @brief Construct a new System object.
     * 0 - FCFS
     * 1 - SJF
     *
     * @param qPcs Quantidade de computadores
     * @param arq Arquivo trace a ser carregado
     * @param politica Política de escalonamento
     */
    System(int qPcs, std::string arq, bool politica) {
        this->qPcs = qPcs;
        this->politica = politica;
        computers = new Computer[qPcs];
        for (int i = 0; i < qPcs; i++) computers[i] = Computer(politica);
        network = new Network(politica);
        loadFile(arq);
    }

    ~System() { delete[] computers; }

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
            std::cout << "Processo com instante " << p.front().getStart()
                      << " enviado para "
                      << "o computador " << i << std::endl;
            computers[i].receiveProcess(p.front());
            p.pop();
        }

        // // Imprime o estado inicial do sistema
        // std::cout << "Estado inicial do sistema: " << std::endl;
        // printPCS();
    }

    void printPCS() {
        std::cout << "COMPUTADORES: " << std::endl;
        for (int i = 0; i < qPcs; i++) {
            std::cout << "Computador " << i << ": ";
            computers[i].print();
        }
        std::cout << "REDE: " << std::endl;
        network->print();
    }
};

#endif  // SYSTEM_H