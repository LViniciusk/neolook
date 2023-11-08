/**
 * @file Network.h
 * @author Júnior Silva (junior.silva@alu.ufc.br) - 554222
 * @author Linyker Vinicius (botlink2030@alu.ufc.br) - 556280
 * @brief Classe que representa a rede do sistema.
 * @version 0.1
 * @date 06-11-2023
 *
 *
 */

#ifndef NETWORK_H
#define NETWORK_H

#include "../TAD'S/PriorityQueue.h"
#include "../TAD'S/Queue.h"
#include "../TAD'S/Vector.h"
#include "Process.h"

/**
 * @brief Classe que representa a rede do sistema.
 *
 */
class Network {
   private:
    Process* process{};           // processo que está sendo executado no disco
    Queue<Process*>* queue;       // fila de processos do disco
    PriorityQueue<Process*>* pq;  // fila de processos do disco
    bool politica;                // politica de escalonamento. 0 - FCFS, 1 - SJF
    bool busy;                    // indica se o disco está ocupado
    unsigned time;                // tempo de execução do processo atual

   public:
    /**
     * @brief Construtor parametrizado da classe Network.
     *
     * @param politica Política de escalonamento do sistema. 0 - FCFS, 1 - SJF
     */
    Network(bool politica) : politica(politica) {
        queue = new Queue<Process*>();
        pq = new PriorityQueue<Process*>();
        busy = false;
    }

    /**
     * @brief Destrutor da classe Network.
     *
     * Libera a memória alocada para a fila de processos e para a fila de prioridades.
     *
     */
    ~Network() {
        delete queue;
        delete pq;
    }

    /**
     * @brief Verifica se a rede está ocupada.
     *
     * @return True, se a rede estiver ocupada. False, caso contrário.
     */
    const bool& isBusy() const { return busy; }

    /**
     * @brief Define o estado da rede.
     *
     * @param b True, se a rede estiver ocupada. False, caso contrário.
     */
    void setBusy(bool b) { busy = b; }

    /**
     * @brief Retorna o processo que está sendo executado na rede.
     *
     * @return Ponteiro para o processo que está sendo executado na rede.
     */
    Process* getProcess() const { return process; }

    /**
     * @brief Função que recebe um processo e o insere na rede. Se a rede estiver ocupada,
     * o processo é inserido na fila de processos. Caso contrário, o processo é
     * inserido diretamente na rede para ser executado.
     *
     * @param p Ponteiro para o processo que será inserido.
     * @return True, se o processo foi inserido diretamente. False, caso o processo
     * tenha sido inserido na fila de processos.
     *
     */
    bool setProcess(Process* p) {
        if (!busy) {
            process = p;
            time = 0;
            busy = true;
            return true;
        } else {
            if (politica) {
                pq->push(p->getNetwork(), p);
            } else {
                queue->push(p);
            }
            return false;
        }
    }

    /**
     * @brief Função que carrega um processo da fila de processos para ser executado.
     *
     * @return True, se um processo foi carregado da fila de processos. False, caso
     * contrário.
     *
     */
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

    /**
     * @brief Função que executa o processo que está na rede. Se o processo terminar de ser executado,
     * a rede é liberada e o processo é retornado. Caso contrário, a rede continua ocupada e a função
     * retorna nullptr.
     *
     * @return Ponteiro para o processo que terminou de ser executado. nullptr, caso o processo ainda
     * não tenha terminado de ser executado.
     */
    Process* execute() {
        if (busy) {
            if (time == process->getNetwork()) {
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
