/**
 * @file CPU.h
 * @author Júnior Silva (junior.silva@alu.ufc.br) - 554222
 * @author Linyker Vinicius (botlink2030@alu.ufc.br) - 556280
 * @brief Classe que representa a CPU do computador.
 * @version 0.1
 * @date 06-11-2023
 *
 *
 */

#ifndef CPU_H
#define CPU_H

#include <iostream>

#include "../TAD'S/PriorityQueue.h"
#include "../TAD'S/Queue.h"
#include "../TAD'S/Vector.h"
#include "Process.h"

class CPU {
   private:
    Process* process;             // processo que está sendo executado na CPU
    Queue<Process*>* queue;       // fila de processos da CPU
    PriorityQueue<Process*>* pq;  // fila de processos da CPU
    bool politica;                // politica de escalonamento. 0 - FCFS, 1 - SJF
    bool busy;                    // indica se a CPU está ocupada
    int time;                     // tempo de execução do processo atual

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
    }

    // getters e setters

    bool isBusy() const { return busy; }

    void setBusy(bool b) { busy = b; }

    Process* getProcess() const { return process; }

    // /**
    //  * @brief Define o processo a ser executado pela CPU.
    //  *
    //  * @param p Processo a ser executado.
    //  */
    bool setProcess(Process* p) {
        if (!busy) {
            process = p;  // insere o processo na CPU
            time = 0;     // reseta o tempo de execução
            busy = true;  // indica que a CPU está ocupada
            return true;  // indica que o processo foi enviado para a execução
                          // na CPU diretamente
        } else {
            if (politica) {
                pq->push(p->getCPU(), p);
            } else {
                queue->push(p);
            }
            return false;  // indica que o processo foi enviado para a fila de
                           // espera da CPU
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

    // /**
    //  * @brief Função que executa o processo na CPU. Se a CPU estiver ocupada,
    //  * verifica se o processo terminou e o retorna. Caso contrário, verifica
    //  se
    //  * há algum processo na fila de processos e o carrega na CPU.
    //  *
    //  * @return Process*
    //  */
    Process* execute() {
        if (busy) {
            if (time == process->getCPU()) {
                busy = false;
                return process;
            } else {
                time++;
            }
        }
        return nullptr;
    }
};

#endif
