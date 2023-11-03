#ifndef SYSTEM_H
#define SYSTEM_H

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "../TAD'S/PriorityQueue.h"
#include "../TAD'S/Queue.h"
#include "../TAD'S/Vector.h"
#include "Computer.h"
#include "Network.h"
#include "Process.h"

class System {
   private:
    int qPcs;                     // quantidade de computadores
    Vector<Computer*> computers;  // computadores do sistema
    Network* network;             // rede do sistema
    bool politica;                // politica de escalonamento
    Queue<Process> queueProcess;  // processos do sistema

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
    System(int qPcs, bool pol) : qPcs(qPcs), politica(pol) {
        network = new Network(politica);
        computers = Vector<Computer*>();
        for (int i = 0; i < qPcs; i++) {
            std::cout << "-Criando computador " << i << std::endl;
            computers.push_back(new Computer(politica, network));
        }
        std::cout << "SISTEMA CRIADO COM SUCESSO" << std::endl;
    }

    ~System() { std::cout << "Sistema destruido" << std::endl; }

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
            queueProcess.push(Process(instant, cpu, disk, network));
        }
        std::cout << "Arquivo carregado" << std::endl;
        std::cout << "\tQuant. Processos: " << queueProcess.size() << std::endl;
        file.close();
    }

    void print() {
        std::cout << "Sistema: " << std::endl;
        std::cout << "\tPolitica: ";
        if (politica)
            std::cout << "SJF" << std::endl;
        else
            std::cout << "FCFS" << std::endl;
        std::cout << "\tQuant. Computadores: " << computers.size() << std::endl;
        std::cout << "\tQuant. Processos Pendentes: " << queueProcess.size()
                  << std::endl;

        if (!queueProcess.empty()) {
            for (auto& p : queueProcess) {
                std::cout << "Process - ";
                std::cout << std::setw(5) << p.getInstant() << " - ";
                std::cout << std::setw(5) << p.getCPU() << " - ";
                std::cout << std::setw(5) << p.getDisk() << " - ";
                std::cout << std::setw(5) << p.getNetwork() << "\n";
            }
        }
    }

    void execute() {
        // Taxa de processamento = n / (instante final - instante inicial)
        int tempoMedioExecucao, tempoMedioEspera, taxaProcessamento;  // TODO
        int timer = 0;
        int pendentes = queueProcess.size();
        srand(123);
        if (queueProcess.empty()) {
            std::cout << "Sem processos para executar" << std::endl;
            return;
        }
        std::cout << "Distribuindo processos" << std::endl;
        std::cout << "Processos restantes: " << pendentes << std::endl;
        while (pendentes) {
            while (!queueProcess.empty() &&
                   queueProcess.front().getInstant() == timer) {
                // escolhe um computador aleatório
                int pc = rand() % qPcs;
                // std::cout << "Time " << timer << " - Processo "
                //           << queueProcess.front().getInstant()
                //           << " enviado para o computador " << pc <<
                //           std::endl;
                computers[pc]->getCPU().setProcess(queueProcess.front());
                queueProcess.pop();
            }

            for (int i = 0; i < qPcs; i++) {
                Process* cpuProcess = computers[i]->getCPU().execute();
                if (cpuProcess != nullptr) {
                    // std::cout << "Time " << timer << " - Processo "
                    //           << cpuProcess->getInstant()
                    //           << " concluido na CPU do computador " << i
                    //           << std::endl;
                    // escolhe um disco aleatório
                    int disk = rand() % 2;
                    computers[i]->getDisk(disk).setProcess(*cpuProcess);
                }
                Process* diskProcess = computers[i]->getDisk(0).execute();
                if (diskProcess != nullptr) {
                    // std::cout << "Time " << timer << " - Processo "
                    //           << diskProcess->getInstant()
                    //           << " concluido no Disco 0 do computador " << i
                    //           << std::endl;
                    network->setProcess(*diskProcess);
                }
                diskProcess = computers[i]->getDisk(1).execute();
                if (diskProcess != nullptr) {
                    // std::cout << "Time " << timer << " - Processo "
                    //           << diskProcess->getInstant()
                    //           << " concluido no Disco 1 do computador " << i
                    //           << std::endl;
                    network->setProcess(*diskProcess);
                }
            }
            Process* aux = network->execute();
            if (aux != nullptr) {
                // std::cout << "Time " << timer << " - Processo "
                //           << aux->getInstant() << " concluido na Rede "
                //           << std::endl;
                // std::cout << "Time " << timer << " - PROCESSO "
                //           << aux->getInstant() << " CONCLUÍDO. -------------
                //           "
                //           << std::endl;
                pendentes--;
            }

            timer++;
        }

        std::cout << "EXECUÇÃO FINALIZADA\n" << std::endl;
        std::cout << "Tempo total de execução: " << timer << std::endl;
    }
};

#endif  // SYSTEM_H