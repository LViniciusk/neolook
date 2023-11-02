#ifndef DISK_H
#define DISK_H

#include "../TAD'S/PriorityQueuePair.h"
#include "../TAD'S/Queue.h"
#include "Process.h"

class Disk {
   private:
    Process* process{};     // processo que está sendo executado no disco
    Queue<Process>* queue;  // fila de processos do disco
    PriorityQueuePair<Process>* pq;  // fila de processos do disco
    bool politica;  // politica de escalonamento. 0 - FCFS, 1 - SJF

   public:
    Disk(bool politica) {
        this->politica = politica;
        queue = new Queue<Process>();
        pq = new PriorityQueuePair<Process>();
    }

    // getters e setters

    /**
     * @brief Retorna o processo que está sendo executado no disco
     *
     * @return Process*
     */
    Process* getProcess() { return process; }

    /**
     * @brief Seta um processo para ser executado no disco. Se o disco já
     * estiver ocupado, o processo é adicionado na fila de processos do disco.
     *
     * @param p Processo a ser executado no disco
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
     * @brief Função que imprime o estado atual do disco
     *
     */
    void print() {
        std::cout << "Disco: " << std::endl;
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

    ~Disk() {
        delete queue;
        delete pq;
    }
};

#endif  // DISK_H