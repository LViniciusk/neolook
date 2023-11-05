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

/**
 * @brief Classe que representa o sistema.
 *
 */
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
        std::cout << "Criando sistema, com " << qPcs << " computadores"
                  << std::endl;
        std::cout << "Politica de escalonamento: ";
        if (politica)
            std::cout << "SJF" << std::endl;
        else
            std::cout << "FCFS" << std::endl;
        process = new Vector<Process>();
        network = new Network(politica);
        computers = Vector<Computer*>();
        timer = -1;
        for (int i = 0; i < qPcs; i++) {
            computers.push_back(new Computer(politica, network));
        }
        std::cout << "SISTEMA CRIADO COM SUCESSO" << std::endl;
    }

    /**
     * @brief Destrutor da classe System.
     *
     */
    ~System() {
        for (int i = 0; i < qPcs; i++) {
            delete computers[i];
        }
        delete network;
        delete process;
        std::cout << "Sistema destruido" << std::endl;
    }

    /**
     * @brief Função que carrega o arquivo trace para o sistema.
     *
     * @param arq Diretório do arquivo trace
     */
    void loadFile(std::string arq) {
        process->clear();
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

    /**
     * @brief Função que imprime o estado atual do sistema.
     *
     */
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
                p.print();
            }
        }
    }

    /**
     * @brief Função que executa o sistema. Enquanto houverem processos não
     * executados, o sistema envia os processos aleatoriamente para as CPUs dos
     * computadores. Quando um processo termina de executar na CPU, ele é
     * enviado para um disco aleatório. Quando o processo termina de executar no
     * disco, ele é enviado para a rede. Quando o processo termina de executar
     * na rede, ele é finalizado.
     *
     */
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
            timer++;
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

    /**
     * @brief Função que calcula o tempo médio de espera, o tempo médio de
     * execução e a taxa de processamento da simulação.
     *
     */
    void calculate() {
        unsigned long totalEspera{}, totalExecucao{};
        for (auto& p : *process) {
            totalEspera += p.getTempoEspera();
            totalExecucao += p.getTempoExecucao();
        }
        tempoMedioEspera = (long double)totalEspera / process->size();
        tempoMedioExecucao = (long double)totalExecucao / process->size();
        taxaProcessamento =
            (long double)process->size() /
            (lastExecuted->getInstanteFinal() - process->begin()->getInstant());
    }
};

#endif  // SYSTEM_H