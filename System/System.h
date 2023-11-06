/**
 * @file System.h
 * @author Júnior Silva (junior.silva@alu.ufc.br) - 554222
 * @author Linyker Vinicius (botlink2030@alu.ufc.br) - 556280
 * @brief Classe que representa o sistema.
 * @version 0.1
 * @date 06-11-2023
 *
 *
 */

#ifndef SYSTEM_H
#define SYSTEM_H

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

#include "../TAD'S/Vector.h"
#include "Computer.h"
#include "Event.h"
#include "LogFile.h"
#include "Network.h"
#include "Process.h"

/**
 * @brief Classe que representa o sistema como um todo.
 * Possui um vetor de computadores, uma rede e um vetor de processos.
 * Possui também um vetor de eventos, que é utilizado para gerar o log do sistema.
 * Possui um relógio lógico, que é incrementado a cada iteração do loop principal.
 * Possui também o tempo médio de espera, o tempo médio de execução e a taxa de processamento do sistema.
 *
 */
class System {
   private:
    int qPcs;                          // quantidade de computadores
    Vector<Computer*> computers;       // computadores do sistema
    Network* network;                  // rede do sistema
    bool politica;                     // politica de escalonamento
    Vector<Process>* processos{};      // vetor de processos
    Event* log{};                      // vetor de eventos do sistema
    long long timer{};                 // relógio lógico do sistema
    long double tempoMedioEspera{};    // tempo médio de espera do sistema
    long double tempoMedioExecucao{};  // tempo médio de execução do sistema
    long double taxaProcessamento{};   // taxa de processamento do sistema

   public:
    /**
     * @brief Construtor parametrizado da classe System.
     * Cria um vetor de computadores, uma rede e um vetor de processos.
     * O timer é inicializado com -1, pois o primeiro processo chega no instante 0.
     *
     * @param qPcs Quantidade de computadores
     * @param arq Arquivo trace a ser carregado
     * @param politica Política de escalonamento. 0 - FCFS, 1 - SJF
     */
    System(int qPcs, bool pol) : qPcs(qPcs), politica(pol) {
        timer = -1;
        processos = new Vector<Process>();
        network = new Network(politica);
        computers = Vector<Computer*>();
        for (int i = 0; i < qPcs; i++) {
            computers.push_back(new Computer(politica, network));
        }
    }

    /**
     * @brief Destrutor da classe System.
     * Libera a memória alocada para os computadores, a rede, o vetor de processos e o vetor de eventos.
     *
     */
    ~System() {
        for (int i = 0; i < qPcs; i++) {
            delete computers[i];
        }
        delete network;
        delete processos;
        delete[] log;
    }

    /**
     * @brief Função que carrega o arquivo trace para o vetor de processos.
     *
     * @param arq Arquivo trace a ser carregado
     */
    void loadFile(std::string arq) {
        processos->clear();
        std::ifstream file(arq);
        int id{}, instant{}, cpu{}, disk{}, network{};
        while (file >> instant >> cpu >> disk >> network) {
            processos->push_back(Process(id++, instant, cpu, disk, network));
        }
        file.close();

        // cria o vetor de eventos
        log = new Event[processos->size()];
    }

    /**
     * @brief Função que executa o sistema.
     * O sistema é executado enquanto houverem processos pendentes.
     * A cada iteração do loop principal:
     * -    O timer é incrementado
     * -    Os processos que chegam no instante atual são enviados para a CPU
     * -    Para cada computador:
     *     -   Se a CPU estiver ociosa, o processo é carregado da fila de processos
     *     -   Se a CPU estiver ocupada, o processo é executado
     *     -   Se o processo terminar na CPU, ele é enviado para um disco aleatório
     * -    Para cada disco:
     *     -   Se o disco estiver ocioso, o processo é carregado da fila de processos
     *     -   Se o disco estiver ocupado, o processo é executado
     *     -    Se o processo terminar no disco, ele é enviado para a rede
     * -    Para a rede:
     *     -    Se a rede estiver ociosa, o processo é carregado da fila de processos
     *     -    Se a rede estiver ocupada, o processo é executado
     *     -    Se o processo terminar na rede, ele é removido do sistema
     * -    O loop principal é encerrado quando não houverem mais processos pendentes
     *
     * Após a execução do sistema, são calculados o tempo médio de espera,
     * o tempo médio de execução e a taxa de processamento.
     * Por fim, o log do sistema é impresso no arquivo log.txt.
     *
     */
    void execute() {
        LogFile* logFile = new LogFile();
        int pendentes = processos->size();                  // quantidade de processos pendentes
        srand(time(NULL));                                  // semente para gerar números aleatórios
        Vector<Process>::iterator it = processos->begin();  // iterador para percorrer o vetor de processos
        logFile->headerMessage(pendentes, politica, qPcs);  // imprime o cabeçalho do log

        while (pendentes) {
            timer++;  // incrementa o relógio lógico
            while (it != processos->end() && it->getInstant() == timer) {
                // escolhe um computador aleatório
                int pc = rand() % qPcs;
                // soma as demandas no total de execução
                log[it->getId()].tempoExecucao = it->getCPU() + it->getDisk() + it->getNetwork();
                if (computers[pc]->getCPU().setProcess(&(*it))) {
                    log[it->getId()].instanteCPU = timer;
                    // logFile->directExecutionCPU(timer, it->getId(), pc);
                } else {
                    // logFile->loadIntoQueueCPU(timer, it->getId(), pc);
                }
                it++;
            }

            for (int i = 0; i < qPcs; i++) {
                // CPU ------------------------------------------------
                if (!computers[i]->getCPU().isBusy()) {
                    if (computers[i]->getCPU().loadFromQueue()) {
                        int idProcess = computers[i]->getCPU().getProcess()->getId();
                        // logFile->loadedFromQueueCPU(timer, idProcess, i);
                        log[idProcess].tempoEspera += timer - computers[i]->getCPU().getProcess()->getInstant();
                        log[idProcess].tempoExecucao += log[idProcess].tempoEspera;
                    }
                } else {
                    Process* p = computers[i]->getCPU().execute();
                    if (p != nullptr) {  // se o processo terminou na CPU
                        // logFile->executionCompletedCPU(timer, p->getId(), i);
                        // Escolhe um disco aleatório
                        int disk = rand() % 2;
                        if (computers[i]->getDisk(disk).setProcess(p)) {
                            // logFile->directExecutionDisk(timer, p->getId(), disk, i);
                        } else {
                            // logFile->loadedIntoQueueDisk(timer, p->getId(), disk, i);
                        }
                    }
                }

                // DISCOS  ----------------------------------------------
                for (int j = 0; j < 2; j++) {
                    if (!computers[i]->getDisk(j).isBusy()) {
                        if (computers[i]->getDisk(j).loadFromQueue()) {
                            int idProcess = computers[i]->getDisk(j).getProcess()->getId();
                            // logFile->loadFromQueueDisk(timer, idProcess, j, i);
                            log[idProcess].tempoEspera += timer - (computers[i]->getDisk(j).getProcess()->getInstant() +
                                                                   computers[i]->getDisk(j).getProcess()->getCPU());
                            log[idProcess].tempoExecucao += log[idProcess].tempoEspera;
                        }
                    } else {
                        Process* p = computers[i]->getDisk(j).execute();
                        if (p != nullptr) {
                            // logFile->executionCompletedDisk(timer, p->getId(), j, i);
                            if (network->setProcess(p)) {
                                // logFile->directExecutionNetwork(timer, p->getId());
                            } else {
                                // logFile->loadedIntoQueueNetwork(timer, p->getId());
                            }
                        }
                    }
                }
            }

            // REDE ------------------------------------------------
            if (!network->isBusy()) {
                if (network->loadFromQueue()) {
                    int idProcess = network->getProcess()->getId();
                    // logFile->loadFromQueueNetwork(timer, idProcess);
                    log[idProcess].tempoEspera += timer - network->getProcess()->getInstant();
                    log[idProcess].tempoExecucao += log[idProcess].tempoEspera;
                }
            } else {
                Process* p = network->execute();
                if (p != nullptr) {
                    // logFile->executionCompletedNetwork(timer, p->getId());
                    log->instanteFinal = timer;
                    // logFile->processFinished(timer, p->getId());
                    pendentes--;
                }
            }
        }
        std::cout << "Quantidade de processos: " << processos->size() << std::endl;
        std::cout << "Tempo total de execução: " << timer << std::endl;
        calculate();
        std::cout << "Tempo médio de espera: " << tempoMedioEspera << std::endl;
        std::cout << "Tempo médio de execução: " << tempoMedioExecucao << std::endl;
        std::cout << "Taxa de processamento: " << taxaProcessamento << std::endl;
        logFile->executionCompleted();
        logFile->statistics(timer, tempoMedioExecucao, tempoMedioEspera, taxaProcessamento);
        delete logFile;
    }

    /**
     * @brief Função que calcula o tempo médio de espera, o tempo médio de execução
     * e a taxa de processamento do sistema.
     *
     */
    void calculate() {
        int qtdProcessos = processos->size();
        unsigned long totalEspera{}, totalExecucao{};
        for (int i = 0; i < qtdProcessos; i++) {
            totalEspera += log[i].tempoEspera;
            totalExecucao += log[i].tempoExecucao;
        }
        tempoMedioEspera = (long double)totalEspera / qtdProcessos;
        tempoMedioExecucao = (long double)totalExecucao / qtdProcessos;
        taxaProcessamento = (long double)qtdProcessos / (timer - processos->front().getInstant());
    }
};

#endif  // SYSTEM_H
