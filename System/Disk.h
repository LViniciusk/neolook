#ifndef DISK_H
#define DISK_H

#include "../TAD'S/PriorityQueuePair.h"
#include "../TAD'S/Queue.h"
#include "Process.h"

class Disk {
   private:
    Process* process{};      // processo que está sendo executado no disco
    Queue<Process*>* queue;  // fila de processos do disco
    PriorityQueuePair<Process*>* pq;  // fila de processos do disco
    bool politica;  // politica de escalonamento. 0 - FCFS, 1 - SJF
    bool busy;      // indica se o disco está ocupado
    int time;       // tempo de execução do processo atual

   public:
    /**
     * @brief Classe que representa o disco do sistema.
     *
     * @param politica Política de escalonamento. 0 - FCFS, 1 - SJF
     */
    Disk(bool politica) : politica(politica) {
        queue = new Queue<Process*>();
        pq = new PriorityQueuePair<Process*>();
        busy = false;
        std::cout << "\tDisco criado" << std::endl;
    }

    /**
     * @brief Destrói o objeto Disco e libera a memória alocada para as filas.
     *
     */
    ~Disk() {
        delete queue;
        delete pq;
        std::cout << "Disco destruido" << std::endl;
    }

    /**
     * @brief Seta um processo para ser executado no disco. Se o disco já
     * estiver ocupado, o processo é adicionado na fila de processos do disco.
     *
     * @param p Processo a ser executado no disco
     */
    void setProcess(Process* p, const long long& timeSystem) {
        p->setInstanteDisco(timeSystem);
        if (!busy) {
            process = p;
            busy = true;
            time = 0;
            // std::cout << "Time " << timeSystem << " - Processo " <<
            // p->getId()
            //           << " inserido no Disco" << std::endl;
        } else {
            if (politica) {
                pq->push(p->getDisk(), p);
            } else {
                queue->push(p);
            }
            // std::cout << "Time " << timeSystem << " - Processo " <<
            // p->getId()
            //           << " inserido na fila do Disco" << std::endl;
        }
    }

    /**
     * @brief Função que executa o processo no disco. Se o disco estiver
     * ocupada, verifica se o processo terminou e o retorna. Caso contrário,
     * verifica se há algum processo na fila de processos e o carrega no disco.
     *
     * @return Process*
     */
    Process* execute(const long long& timeSystem) {
        if (busy) {
            if (time == process->getDisk()) {
                // std::cout << "Time " << timeSystem << " - Processo "
                //           << process->getId() << " concluido no Disco"
                //           << std::endl;
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
                    process->setTempoEsperaDisco(timeSystem -
                                                 (process->getInstanteCPU()));
                    // std::cout
                    //     << "Time " << timeSystem << " - Processo "
                    //     << process->getId()
                    //     << " inserido na fila do Disco - Espera = " << espera
                    //     << std::endl;
                }
            } else {
                if (!queue->empty()) {
                    process = queue->front();
                    queue->pop();
                    busy = true;
                    time = 0;
                    process->setTempoEsperaDisco(timeSystem -
                                                 (process->getInstanteCPU()));
                    // std::cout
                    //     << "Time " << timeSystem << " - Processo "
                    //     << process->getId()
                    //     << " inserido na fila do Disco - Espera = " << espera
                    //     << std::endl;
                }
            }
        }
        return nullptr;
    }
};

#endif  // DISK_H