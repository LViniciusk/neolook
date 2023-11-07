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
#include <iomanip>
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
    unsigned qPcs;                 // quantidade de computadores
    Vector<Computer*> computers;   // computadores do sistema
    Network* network;              // rede do sistema
    bool politica;                 // politica de escalonamento
    Vector<Process>* processos{};  // vetor de processos
    Event* log{};                  // vetor de eventos do sistema
    unsigned timer{};              // relógio lógico do sistema
    double tempoMedioEspera{};     // tempo médio de espera do sistema
    double tempoMedioExecucao{};   // tempo médio de execução do sistema
    double taxaProcessamento{};    // taxa de processamento do sistema
    bool printLog{};               // flag para imprimir o log do sistema
    LogFile* logFile{};            // arquivo de log

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
    System(int qPcs, bool pol, bool printLog = false) : qPcs(qPcs), politica(pol), printLog(printLog) {
        processos = new Vector<Process>();
        logFile = new LogFile(&timer, printLog);
        network = new Network(politica, logFile);
        computers = Vector<Computer*>();
        for (int i = 0; i < qPcs; i++) {
            computers.push_back(new Computer(politica, network, logFile));
        }
    }

    /**
     * @brief Destrutor da classe System.
     * Libera a memória alocada para os computadores, a rede, o vetor de processos e o vetor de eventos.
     *
     */
    ~System() {
        for (unsigned i = 0; i < qPcs; i++) {
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
        unsigned id{}, instant{}, cpu{}, disk{}, network{};
        while (file >> instant >> cpu >> disk >> network) {
            processos->push_back(Process(id++, instant, cpu, disk, network));
        }
        file.close();

        // cria o vetor de eventos
        log = new Event[processos->size()];
    }

    void verifyQueues() {
        if (!network->isBusy()) {
            if (network->loadFromQueue()) {
                Process* p = network->getProcess();
                log[p->getId()].tempoEspera += timer - (p->getNetwork() + log[p->getId()].instanteRede);
            }
        }

        for (unsigned pc = 0; pc < qPcs; ++pc) {
            // DISCOS --------------------------------------------
            for (unsigned j = 0; j < 2; ++j) {
                Disk& d = computers[pc]->getDisk(j);
                if (!d.isBusy()) {
                    if (d.loadFromQueue()) {
                        Process* p = d.getProcess();
                        log[p->getId()].tempoEspera += timer - (p->getDisk() + log[p->getId()].instanteDisco);
                    }
                }
            }
            // CPU -----------------------------------------------
            CPU& cpu = computers[pc]->getCPU();
            if (!cpu.isBusy()) {
                if (computers[pc]->getCPU().loadFromQueue()) {
                    Process* p = cpu.getProcess();
                    log[p->getId()].tempoEspera += timer - p->getInstant();
                }
            }
        }
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
        int pendentes = processos->size();  // quantidade de processos pendentes
        // std::srand(time(NULL));             // semente para gerar números aleatórios
        std::srand(123);                                    // semente para gerar números aleatórios
        Vector<Process>::iterator it = processos->begin();  // iterador para percorrer o vetor de processos
        logFile->headerMessage(pendentes, politica, qPcs);  // imprime o cabeçalho do log

        while (true) {
            // CARREGA O PROCESSO NO COMPUTADOR.
            // Como o primeiro recurso é a CPU, o processo é enviado para a CPU.
            // Se a CPU estiver ocupada, o processo é enviado para a fila de espera.

            while (it != processos->end() && it->getInstant() == timer) {
                // escolhe um computador aleatório
                int pc = rand() % qPcs;
                // soma as demandas no total de execução
                log[it->getId()].tempoExecucao = it->getCPU() + it->getDisk() + it->getNetwork();
                if (computers[pc]->getCPU().setProcess(&(*it))) {
                    log[it->getId()].instanteCPU = timer;
                }
                it++;
            }

            // Se o recurso está vazio, resgata da fila de espera

            // verifyQueues();

            // Verifica se os processos na CPU e nos discos foram finalizados e enviam para o próximo recurso.
            // Se o processo na rede foi finalizado, termina o processo.

            // REDE --------------------------------------------------

            if (network->isConcluded()) {
                Process* p = network->getProcess();
                logFile->executionCompletedNetwork(p->getId());
                logFile->processFinished(p->getId());
                Event& event = log[p->getId()];
                event.instanteFinal = timer;
                event.tempoExecucao = event.tempoEspera + (p->getCPU() + p->getDisk() + p->getNetwork());
                event.concluded = true;
                network->removeProcess();
                pendentes--;
                if (!pendentes) break;
            }

            for (unsigned pc = 0; pc < qPcs; ++pc) {
                // DISCOS --------------------------------------------
                for (unsigned j = 0; j < 2; ++j) {
                    Disk& d = computers[pc]->getDisk(j);
                    if (d.isConcluded()) {
                        logFile->executionCompletedDisk(d.getProcess()->getId());
                        network->setProcess(d.getProcess());
                        d.removeProcess();
                    }
                }
                // CPU -----------------------------------------------
                CPU& cpu = computers[pc]->getCPU();
                if (cpu.isConcluded()) {
                    logFile->executionCompletedCPU(cpu.getProcess()->getId());
                    short disk = rand() % 2;
                    computers[pc]->getDisk(disk).setProcess(cpu.getProcess());
                    cpu.removeProcess();
                }
            }

            verifyQueues();

            // Executa os processos nos recursos

            // REDE --------------------------------------------------
            if (network->isBusy()) {
                network->execute();
            }
            for (unsigned pc = 0; pc < qPcs; ++pc) {
                // DISCOS --------------------------------------------
                for (unsigned disk = 0; disk < 2; ++disk) {
                    Disk& d = computers[pc]->getDisk(disk);
                    if (d.isBusy()) {
                        d.execute();
                    }
                }
                // CPU -----------------------------------------------
                CPU& cpu = computers[pc]->getCPU();
                if (cpu.isBusy()) {
                    computers[pc]->getCPU().execute();
                }
            }

            timer++;  // incrementa o relógio lógico
        }

        calculate();
        std::cout << "Política de escalonamento = " << (politica ? "SJF" : "FCFS") << std::endl;
        std::cout << "Quantidade de processos   = " << processos->size() << std::endl;
        std::cout << "Tempo total de execução   = " << timer << std::endl;
        std::cout << "Tempo médio de espera     = " << tempoMedioEspera << std::endl;
        std::cout << "Tempo médio de execução   = " << tempoMedioExecucao << std::endl;
        std::cout << "Taxa de processamento     = " << taxaProcessamento << std::endl;
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
        tempoMedioEspera = (double)totalEspera / qtdProcessos;
        tempoMedioExecucao = (double)totalExecucao / qtdProcessos;
        taxaProcessamento = (double)qtdProcessos / (timer - processos->front().getInstant());
    }
};

#endif  // SYSTEM_H
