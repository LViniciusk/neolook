#ifndef CPU_H
#define CPU_H

#include <iostream>

#include "../TAD'S/PriorityQueuePair.h"
#include "../TAD'S/Queue.h"
#include "Process.h"

class CPU {
   private:
    Process* process{};     // processo que está sendo executado na CPU
    Queue<Process>* queue;  // fila de processos da CPU
    PriorityQueuePair<Process>* pq;  // fila de processos da CPU
    bool politica;  // politica de escalonamento. 0 - FCFS, 1 - SJF

   public:
    CPU(bool politica) : politica(politica) {
        queue = new Queue<Process>();
        pq = new PriorityQueuePair<Process>();
    }

    ~CPU() {
        delete queue;
        delete pq;
    }

    // getters e setters

    /**
     * @brief Retorna o processo que está sendo executado na CPU
     *
     * @return Process*
     */
    Process* getProcess() { return process; }

    /**
     * @brief Seta o processo que está sendo executado na CPU. Se a CPU já
     * estiver ocupada, o processo é adicionado na fila de processos da CPU.
     *
     * @param p Processo a ser executado na CPU
     */
    void setProcess(Process& p) {
        if (process == nullptr) {
            process = &p;
        } else {
            if (politica)
                pq->push(p.getDisk(), p);
            else
                queue->push(p);
        }
    }

    /**
     * @brief Função que imprime o estado atual da CPU
     *
     */
    void print() {
        std::cout << "\tEm execução: ";
        if (process != nullptr)
            process->print();
        else
            std::cout << "Nenhum processo em execução" << std::endl;

        std::cout << "\tFila: " << std::endl;
        if (politica) {
            if (pq->empty())
                std::cout << "\t\tFila vazia" << std::endl;
            else
                for (auto& p : *pq) {
                    p.print();
                }
        } else {
            if (queue->empty())
                std::cout << "\t\tFila vazia" << std::endl;
            else
                for (auto& p : *queue) {
                    p.print();
                }
        }
    }
};

#endif