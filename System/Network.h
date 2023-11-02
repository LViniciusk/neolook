#ifndef NETWORK_H
#define NETWORK_H

#include "../TAD'S/PriorityQueuePair.h"
#include "../TAD'S/Queue.h"
#include "Process.h"

class Network {
   private:
    Process* process{};     // processo que esta sendo executado na rede
    Queue<Process>* queue;  // fila de processos da rede
    PriorityQueuePair<Process>* pq;  // fila de processos da rede
    bool politica;                   // politica de escalonamento. 0 - FCFS, 1 -
                                     // SJF

   public:
    Network(bool politica) : politica(politica) {
        queue = new Queue<Process>();
        pq = new PriorityQueuePair<Process>();
    }

    ~Network() {
        delete queue;
        delete pq;
    }

    // getters e setters
    /**
     * @brief Retorna o processo que esta sendo executado na rede
     *
     * @return Process*
     */
    Process* getProcess() { return process; }

    /**
     * @brief Seta um processo para ser executado na rede. Se a rede já estiver
     * ocupada, o processo é adicionado na fila de processos da rede.
     *
     * @param p Processo a ser executado na rede
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
     * @brief Função que imprime o estado atual da rede
     *
     */
    void print() {
        std::cout << "Rede: " << std::endl;
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

#endif  // NETWORK_H