/**
 * @file Disk.h
 * @author Júnior Silva (junior.silva@alu.ufc.br) - 554222
 * @author Linyker Vinicius (botlink2030@alu.ufc.br) - 556280
 * @brief Classe que representa um Disco do computador.
 * @version 0.1
 * @date 06-11-2023
 *
 *
 */

#ifndef DISK_H
#define DISK_H

#include "../TAD'S/PriorityQueue.h"
#include "../TAD'S/Queue.h"
#include "../TAD'S/Vector.h"
#include "Process.h"

class Disk {
   private:
    Process* process{};           // processo que está sendo executado no disco
    Queue<Process*>* queue;       // fila de processos do disco
    PriorityQueue<Process*>* pq;  // fila de processos do disco
    bool politica;                // politica de escalonamento. 0 - FCFS, 1 - SJF
    bool busy;                    // indica se o disco está ocupado
    int time;                     // tempo de execução do processo atual

   public:
    /**
     * @brief Classe que representa o disco do sistema.
     *
     * @param politica Política de escalonamento. 0 - FCFS, 1 - SJF
     */
    Disk(bool politica) : politica(politica) {
        queue = new Queue<Process*>();
        pq = new PriorityQueue<Process*>();
        busy = false;
    }

    /**
     * @brief Destrói o objeto Disco e libera a memória alocada para as filas.
     *
     */
    ~Disk() {
        delete queue;
        delete pq;
    }

    bool isBusy() const { return busy; }

    void setBusy(bool b) { busy = b; }

    Process* getProcess() const { return process; }

    bool setProcess(Process* p) {
        if (!busy) {
            process = p;  // insere o processo na CPU
            time = 0;     // reseta o tempo de execução
            busy = true;  // indica que a CPU está ocupada
            return true;  // indica que o processo foi enviado para a execução na CPU diretamente
        } else {
            if (politica) {
                pq->push(p->getDisk(), p);
            } else {
                queue->push(p);
            }
            return false;  // indica que o processo foi enviado para a fila de espera da CPU
        }
    }

    bool loadFromQueue() {
        if (politica) {
            if (!pq->empty()) {
                process = pq->top();
                pq->pop();
                busy = true;
                time = 0;
                return true;
            }
        } else {
            if (!queue->empty()) {
                process = queue->front();
                queue->pop();
                busy = true;
                time = 0;
                return true;
            }
        }
        return false;
    }

    Process* execute() {
        if (busy) {
            if (time == process->getDisk()) {
                busy = false;
                return process;
            } else {
                time++;
            }
        }
        return nullptr;
    }
};

#endif  // DISK_H
