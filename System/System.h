#ifndef SYSTEM_H
#define SYSTEM_H

#include <fstream>
#include <iostream>

#include "../TAD'S/PriorityQueue.h"
#include "../TAD'S/Queue.h"
#include "../TAD'S/Vector.h"
#include "Computer.h"
#include "Network.h"
#include "Process.h"

class System {
   private:
    int qPcs;                      // quantidade de computadores
    Computer* computers;           // computadores do sistema
    Network network;               // rede do sistema
    bool politica;                 // politica de escalonamento
    Queue<Process>* queueProcess;  // processos do sistema

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
    System(int qPcs, std::string arq, bool politica)
        : qPcs(qPcs), politica(politica) {
        network = Network(politica);
        computers = new Computer[qPcs];
        for (int i = 0; i < qPcs; i++)
            computers[i] = Computer(politica, &network);
        queueProcess = new Queue<Process>();
        loadFile(arq);
    }

    ~System() {
        delete[] computers;
        delete queueProcess;
        std::cout << "Sistema destruido" << std::endl;
    }

    void loadFile(std::string arq) {
        std::ifstream file(arq);
        if (!file.is_open())
            std::cout << "Erro ao abrir o arquivo" << std::endl;
        int instant, cpu, disk, network;
        while (file >> instant >> cpu >> disk >> network) {
            if (file.bad()) {
                std::cout << "Erro ao ler o arquivo" << std::endl;
                break;
            }
            queueProcess->push(Process(instant, cpu, disk, network));
        }
        std::cout << "Arquivo carregado" << std::endl;
        std::cout << "\tQuant. Processos: " << queueProcess->size()
                  << std::endl;
        file.close();
    }

    void execute() {
        int instant = 0;
        int pendent = queueProcess->size();
        while (pendent) {
            std::cout << "Processo executado no instante " << instant
                      << std::endl;
            pendent--;
            instant++;
        }
    }
};

#endif  // SYSTEM_H