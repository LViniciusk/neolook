#ifndef NETWORK_H
#define NETWORK_H

#include "../TAD'S/PriorityQueuePair.h"
#include "../TAD'S/Queue.h"
#include "Process.h"

class Network {
   private:
    Process process{};      // processo que está sendo executado no disco
    Queue<Process>* queue;  // fila de processos do disco
    PriorityQueuePair<Process>* pq;  // fila de processos do disco
    bool politica;  // politica de escalonamento. 0 - FCFS, 1 - SJF
    bool busy;      // indica se o disco está ocupado
    int time;       // tempo de execução do processo atual

   public:
    /**
     * @brief Construct a new Network object
     *
     * Essa classe é responsável por gerenciar a rede de processos, mantendo uma
     * fila de processos a serem executados e uma fila de processos em execução.
     *
     */
    Network(bool politica) : politica(politica) {
        queue = new Queue<Process>();
        pq = new PriorityQueuePair<Process>();
        busy = false;
        std::cout << "\tRede criada" << std::endl;
    }

    /**
     * @brief Destroy the Network object
     *
     */
    ~Network() { std::cout << "Rede destruida" << std::endl; }

    /**
     * @brief Seta um processo para ser executado na rede. Se a rede já
     * estiver ocupado, o processo é adicionado na fila de processos da rede.
     *
     * @param p Processo a ser executado no rede
     */
    void setProcess(Process& p) {
        if (!busy) {
            process = p;
            busy = true;
            time = 0;
            // std::cout << "\t\tProcesso " << process.getInstant()
            //           << " inserido na Rede" << std::endl;
        } else {
            if (politica) {
                pq->push(p.getCPU(), p);
            } else {
                queue->push(p);
            }
            // std::cout << "\t\tProcesso " << p.getInstant()
            //           << " inserido na fila da Rede" << std::endl;
        }
    }

    /**
     * @brief Função que executa o processo na rede. Se a rede estiver
     * ocupada, verifica se o processo terminou e o retorna. Caso contrário,
     * verifica se há algum processo na fila de processos e o carrega na rede.
     *
     * @return Process*
     */
    Process* execute() {
        if (busy) {
            if (time == process.getDisk()) {
                // std::cout << "\t\tProcesso " << process.getInstant()
                //           << " concluido na Disco" << std::endl;
                busy = false;
                return &process;
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
                    // std::cout << "\t\tProcesso " << process.getInstant()
                    //           << " inserido na fila do Disco" << std::endl;
                }
            } else {
                if (!queue->empty()) {
                    process = queue->front();
                    queue->pop();
                    busy = true;
                    time = 0;
                    // std::cout << "\t\tProcesso " << process.getInstant()
                    //           << " inserido na fila do Disco" << std::endl;
                }
            }
        }
        return nullptr;
    }
};

#endif  // DISK_H