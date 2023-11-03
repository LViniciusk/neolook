#ifndef DISK_H
#define DISK_H

#include "../TAD'S/PriorityQueuePair.h"
#include "../TAD'S/Queue.h"
#include "Process.h"

class Disk {
   private:
    Process process{};      // processo que está sendo executado no disco
    Queue<Process>* queue;  // fila de processos do disco
    PriorityQueuePair<Process>* pq;  // fila de processos do disco
    bool politica;  // politica de escalonamento. 0 - FCFS, 1 - SJF
    bool busy;      // indica se o disco está ocupado
    int time;       // tempo de execução do processo atual

   public:
    Disk(bool politica) : politica(politica) {
        queue = new Queue<Process>();
        pq = new PriorityQueuePair<Process>();
        busy = false;
        std::cout << "\tDisco criado" << std::endl;
    }

    ~Disk() {
        delete queue;
        delete pq;
        std::cout << "Disco destruido" << std::endl;
    }

    /**
     * @brief Seta um processo para ser executado no disco. Se o disco já
     * estiver ocupado, o processo é adicionado na fila de processos do
     disco.
     *
     * @param p Processo a ser executado no disco
     */
    void setProcess(Process& p) {
        if (!busy) {
            process = p;
            busy = true;
            time = 0;
            // std::cout << "\t\tProcesso inserido no Disco" << std::endl;
        } else {
            if (politica) {
                pq->push(p.getCPU(), p);
            } else {
                queue->push(p);
            }
            // std::cout << "\t\tProcesso " << p.getInstant()
            //           << " inserido na fila do Disco" << std::endl;
        }
    }

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