#ifndef CPU_H
#define CPU_H

#include <iostream>

#include "../TAD'S/PriorityQueue.h"
#include "../TAD'S/Queue.h"
#include "Process.h"

/**
 * @brief Classe que representa a CPU do computador.
 *
 */
class CPU {
   private:
    Process* process{};           // processo que está sendo executado na CPU
    Queue<Process*>* queue;       // fila de processos da CPU
    PriorityQueue<Process*>* pq;  // fila de processos da CPU
    bool politica;  // politica de escalonamento. 0 - FCFS, 1 - SJF
    bool busy;      // indica se a CPU está ocupada
    int time;       // tempo de execução do processo atual

   public:
    /**
     * @brief Classe que representa a CPU do sistema.
     *
     */
    CPU() = default;

    /**
     * @brief Classe que representa a CPU do sistema.
     *
     * Essa classe é responsável por gerenciar a execução dos processos no
     * sistema. Ela possui uma fila de processos e uma fila de prioridades, além
     * de uma política de escalonamento.
     *
     */
    CPU(bool politica) : politica(politica) {
        queue = new Queue<Process*>();
        pq = new PriorityQueue<Process*>();
        busy = false;
    }

    /**
     * @brief Destrutor da classe CPU.
     *
     * Libera a memória alocada para a fila de processos e a fila de
     * prioridades. Imprime uma mensagem informando que a CPU foi destruída.
     */
    ~CPU() {
        delete queue;
        delete pq;
        std::cout << "CPU destruida" << std::endl;
    }

    /**
     * @brief Define o processo a ser executado pela CPU.
     *
     * @param p Processo a ser executado.
     */
    void setProcess(Process* p, const long long& timeSystem) {
        if (!busy) {
            p->setInstanteCPU(timeSystem);
            process = p;
            time = 0;
            busy = true;
            // std::cout << "Time " << timeSystem << " - Processo " <<
            // p->getId()
            //           << " inserido na CPU" << std::endl;
        } else {
            if (politica) {
                pq->push(p->getCPU(), p);
            } else {
                queue->push(p);
            }
            // std::cout << "Time " << timeSystem << " - Processo " <<
            // p->getId()
            //           << " inserido na fila da CPU" << std::endl;
        }
    }

    /**
     * @brief Função que executa o processo na CPU. Se a CPU estiver ocupada,
     * verifica se o processo terminou e o retorna. Caso contrário, verifica se
     * há algum processo na fila de processos e o carrega na CPU.
     *
     * @return Process*
     */
    Process* execute(const long long& timeSystem) {
        if (busy) {
            if (time == process->getCPU()) {
                busy = false;
                return process;
            } else {
                time++;
            }
        } else {
            if (politica) {
                if (!pq->empty()) {
                    process = pq->top();
                    pq->pop();
                    busy = true;
                    time = 0;
                    process->setInstanteCPU(timeSystem);
                    // std::cout << "Time " << timeSystem << " - Processo "
                    //           << process->getId() << " carregado da fila da
                    //           CPU"
                    //           << std::endl;
                }
            } else {
                if (!queue->empty()) {
                    process = queue->front();
                    queue->pop();
                    busy = true;
                    time = 0;
                    process->setInstanteCPU(timeSystem);
                    // std::cout << "Time " << timeSystem << " - Processo "
                    //           << process->getId() << " carregado da fila da
                    //           CPU"
                    //           << std::endl;
                }
            }
        }
        return nullptr;
    }
};

#endif