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

// Tempo médio de execução: o tempo de execução de um processo inclui não
// somente os tempos de processamento em cada recurso, mas também os tempos de
// espera em cada fila de cada recurso.

// Tempo médio de espera: o tempo de espera de um processo consiste na soma dos
// tempos de espera em cada fila de cada recurso. Você deve contabilizar os
// tempos de espera de cada processo simulado e, ao final, calcular a média.

// Taxa de processamento: taxa de processamento consiste na razão do número
// total de processos executados pelo intervalo de tempo decorrente desde o
// início do primeiro processo até o término do último. Logo, se o primeiro
// processo foi iniciado no instante t1 e o n-ésimo (último) foi finalizado no
// instante t2, a taxa de processamento é calculada como n/(t2 − t1).

class System {
   private:
    int qPcs;                          // quantidade de computadores
    Vector<Computer*> computers;       // computadores do sistema
    Network* network;                  // rede do sistema
    bool politica;                     // politica de escalonamento
    Vector<Process>* process;          // processos do sistema
    long long timer{};                 // relógio lógico do sistema
    long double tempoMedioEspera{};    // tempo médio de espera do sistema
    long double tempoMedioExecucao{};  // tempo médio de execução do sistema
    long double taxaProcessamento{};   // taxa de processamento do sistema
    Process* lastExecuted{};           // último processo executado

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
        process = new Vector<Process>();
        network = new Network(politica);
        computers = Vector<Computer*>();
        for (int i = 0; i < qPcs; i++) {
            std::cout << "-Criando computador " << i << std::endl;
            computers.push_back(new Computer(politica, network));
        }
        std::cout << "SISTEMA CRIADO COM SUCESSO" << std::endl;
    }

    ~System() {
        for (int i = 0; i < qPcs; i++) {
            delete computers[i];
        }
        delete network;
        delete process;
        std::cout << "Sistema destruido" << std::endl;
    }

    void loadFile(std::string arq) {
        std::ifstream file(arq);
        if (!file.is_open())
            std::cout << "Erro ao abrir o arquivo" << std::endl;
        int instant, cpu, disk, network, id{};
        while (file >> instant >> cpu >> disk >> network) {
            if (file.bad()) {
                std::cout << "Erro ao ler o arquivo" << std::endl;
                break;
            }
            process->push_back(Process(id++, instant, cpu, disk, network));
        }
        std::cout << "Arquivo carregado" << std::endl;
        std::cout << "\tQuant. Processos: " << process->size() << std::endl;
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
        std::cout << "\tQuant. Processos Pendentes: " << process->size()
                  << std::endl;

        if (!process->empty()) {
            for (auto& p : *process) {
                std::cout << "Process - ";
                std::cout << std::setw(5) << p.getInstant() << " - ";
                std::cout << std::setw(5) << p.getCPU() << " - ";
                std::cout << std::setw(5) << p.getDisk() << " - ";
                std::cout << std::setw(5) << p.getNetwork() << " - ";
                std::cout << std::setw(5) << p.getInstanteFinal() << " - ";
                std::cout << std::setw(5) << p.getExecutado() << " - ";
                std::cout << std::setw(5) << p.getTempoEsperaCPU() << " - ";
                std::cout << std::setw(5) << p.getTempoEsperaDisco() << " - ";
                std::cout << std::setw(5) << p.getTempoEsperaRede() << " - ";
                std::cout << std::setw(5) << p.getTempoEspera() << " - ";
                std::cout << std::setw(5) << p.getTempoExecucao() << "\n";
            }
        }
    }

    void execute() {
        int pendentes = process->size();
        // cria um iterador para percorrer o vetor de processos, e um iterador
        // para o final do vetor
        Vector<Process>::iterator it = process->begin();
        Vector<Process>::iterator last = process->end();
        srand(123);
        if (pendentes == 0) {
            std::cout << "Sem processos para executar" << std::endl;
            return;
        }
        std::cout << "Distribuindo processos" << std::endl;
        std::cout << "Processos restantes: " << pendentes << std::endl;
        while (pendentes) {
            while (it != last && it->getInstant() == timer) {
                // escolhe um computador aleatório
                int pc = rand() % qPcs;
                // std::cout << "Time " << timer << " - Processo " <<
                // it->getId()
                //           << " enviado para o computador " << pc <<
                //           std::endl;
                computers[pc]->getCPU().setProcess(&(*it), timer);
                it++;
            }

            for (int i = 0; i < qPcs; i++) {
                Process* cpuProcess = computers[i]->getCPU().execute(timer);
                if (cpuProcess != nullptr) {
                    // std::cout << "Time " << timer << " - Processo "
                    //           << cpuProcess->getId()
                    //           << " concluido na CPU do computador " << i
                    //           << std::endl;
                    // escolhe um disco aleatório
                    int disk = rand() % 2;
                    computers[i]->getDisk(disk).setProcess(cpuProcess, timer);
                }
                Process* diskProcess = computers[i]->getDisk(0).execute(timer);
                if (diskProcess != nullptr) {
                    // std::cout << "Time " << timer << " - Processo "
                    //           << diskProcess->getId()
                    //           << " concluido no Disco 0 do computador " << i
                    //           << std::endl;
                    network->setProcess(diskProcess, timer);
                }
                diskProcess = computers[i]->getDisk(1).execute(timer);
                if (diskProcess != nullptr) {
                    // std::cout << "Time " << timer << " - Processo "
                    //           << diskProcess->getId()
                    //           << " concluido no Disco 1 do computador " << i
                    //           << std::endl;
                    network->setProcess(diskProcess, timer);
                }
            }
            Process* aux = network->execute(timer);
            if (aux != nullptr) {
                // std::cout << "Time " << timer << " - Processo " <<
                // aux->getId()
                //           << " concluido na Rede " << std::endl;
                // std::cout << "Time " << timer << " - PROCESSO " <<
                // aux->getId()
                //           << " CONCLUÍDO. -------------" << std::endl;
                aux->setInstanteFinal(timer);
                aux->setExecutado(true);
                pendentes--;
                lastExecuted = aux;
            }

            timer++;
        }

        std::cout << "EXECUÇÃO FINALIZADA\n" << std::endl;
        std::cout << "Tempo total de execução: " << timer << std::endl;
        calculate();
        std::cout << "Tempo médio de espera: " << tempoMedioEspera << std::endl;
        std::cout << "Tempo médio de execução: " << tempoMedioExecucao
                  << std::endl;
        std::cout << "Taxa de processamento: " << taxaProcessamento
                  << std::endl;
    }

    void calculate() {
        int totalEspera{}, totalExecucao{};
        for (auto& p : *process) {
            totalEspera += p.getTempoEspera();
            totalExecucao += p.getTempoExecucao();
        }
        tempoMedioEspera = (long double)totalEspera / process->size();
        tempoMedioExecucao = (long double)totalExecucao / process->size();
        taxaProcessamento =
            (long double)process->size() /
            (lastExecuted->getInstanteFinal() - process->front().getInstant());
    }
};

#endif  // SYSTEM_H