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
#include "Event.h"
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
    Vector<Process>* processos{};      // vetor de processos
    Vector<Event>* events{};           // vetor de eventos do sistema
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
        std::cout << "Criando sistema, com " << qPcs << " computadores"
                  << std::endl;
        std::cout << "Politica de escalonamento: ";
        if (politica)
            std::cout << "SJF" << std::endl;
        else
            std::cout << "FCFS" << std::endl;
        events = new Vector<Event>();
        processos = new Vector<Process>();
        network = new Network(politica, events);
        computers = Vector<Computer*>();
        for (int i = 0; i < qPcs; i++) {
            computers.push_back(new Computer(politica, network, events));
        }
        std::cout << "SISTEMA CRIADO COM SUCESSO" << std::endl;
    }

    ~System() {
        for (int i = 0; i < qPcs; i++) {
            delete computers[i];
        }
        delete network;
        delete events;
        std::cout << "Sistema destruido" << std::endl;
    }

    void loadFile(std::string arq) {
        events->clear();
        processos->clear();
        std::ifstream file(arq);
        if (!file.is_open())
            std::cout << "Erro ao abrir o arquivo" << std::endl;
        int id{}, instant{}, cpu{}, disk{}, network{};
        while (file >> instant >> cpu >> disk >> network) {
            processos->push_back(Process(id++, instant, cpu, disk, network));
            events->push_back(Event(&processos->back()));
        }
        std::cout << "Arquivo carregado" << std::endl;
        std::cout << "\tQuant. Processos: " << events->size() << std::endl;
        file.close();

        for (auto& p : *processos) {
            std::cout << "Processo " << p.getId()
                      << " - Instante: " << p.getInstant()
                      << " - CPU: " << p.getCPU() << " - Disco: " << p.getDisk()
                      << " - Rede: " << p.getNetwork() << std::endl;
        }
    }

    void print() {
        std::cout << "Sistema: " << std::endl;
        std::cout << "\tPolitica: ";
        if (politica)
            std::cout << "SJF" << std::endl;
        else
            std::cout << "FCFS" << std::endl;
        std::cout << "\tQuant. Computadores: " << computers.size() << std::endl;
        std::cout << "\tQuant. Processos Pendentes: " << events->size()
                  << std::endl;

        if (!events->empty()) {
            for (auto& e : *events) {
                e.print();
            }
        }
    }

    void execute() {
        int pendentes = events->size();
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
            while (it != last && it->process->getInstant() == timer) {
                // escolhe um computador aleatório
                int pc = rand() % qPcs;
                std::cout << "Time " << timer << " - Processo "
                          << it->process->getId()
                          << " enviado para o computador " << pc << std::endl;
                computers[pc]->getCPU().setProcess(&(*it), timer);
                it++;
            }

            for (int i = 0; i < qPcs; i++) {
                Process* cpuProcess = computers[i]->getCPU().execute(timer);
                if (cpuProcess != nullptr) {
                    std::cout << "Time " << timer << " - Processo "
                              << cpuProcess->getId()
                              << " concluido na CPU do computador " << i
                              << std::endl;
                    // escolhe um disco aleatório
                    int disk = rand() % 2;
                    computers[i]->getDisk(disk).setProcess(
                        &(events->at(cpuProcess->getId())), timer);
                }
                Process* diskProcess = computers[i]->getDisk(0).execute(timer);
                if (diskProcess != nullptr) {
                    std::cout << "Time " << timer << " - Processo "
                              << diskProcess->getId()
                              << " concluido no Disco 0 do computador " << i
                              << std::endl;
                    network->setProcess(&(events->at(diskProcess->getId())),
                                        timer);
                }
                diskProcess = computers[i]->getDisk(1).execute(timer);
                if (diskProcess != nullptr) {
                    std::cout << "Time " << timer << " - Processo "
                              << diskProcess->getId()
                              << " concluido no Disco 1 do computador " << i
                              << std::endl;
                    network->setProcess(&(events->at(diskProcess->getId())),
                                        timer);
                }
            }
            Process* networkProcess = network->execute(timer);
            if (networkProcess != nullptr) {
                std::cout << "Time " << timer << " - Processo "
                          << networkProcess->getId() << " concluido na Rede "
                          << std::endl;
                std::cout << "Time " << timer << " - PROCESSO "
                          << networkProcess->getId()
                          << " CONCLUÍDO. -------------" << std::endl;
                events->at(networkProcess->getId()).instanteFinal = timer;
                events->at(networkProcess->getId()).concluded = true;
                pendentes--;
                lastExecuted = networkProcess;
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
        unsigned long totalEspera{}, totalExecucao{};
        for (auto& e : *events) {
            totalEspera += e.tempoEspera;
            totalExecucao += e.tempoExecucao;
        }
        tempoMedioEspera = (long double)totalEspera / events->size();
        tempoMedioExecucao = (long double)totalExecucao / events->size();
        taxaProcessamento = (long double)events->size() /
                            (events->back().instanteFinal -
                             events->front().process->getInstant());
    }
};

#endif  // SYSTEM_H