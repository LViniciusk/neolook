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
#include "LogFile.h"
#include "Process.h"

/**
 * @brief Classe que representa a CPU do computador.
 *
 */
class CPU {
   private:
    Process* process;             // processo que está sendo executado na CPU
    Queue<Process*>* queue;       // fila de processos da CPU
    PriorityQueue<Process*>* pq;  // fila de processos da CPU
    bool politica;                // politica de escalonamento. 0 - FCFS, 1 - SJF
    bool busy;                    // indica se a CPU está ocupada
    bool concluded{false};        // indica se o processo terminou de ser executado
    unsigned counter;             // tempo de execução do processo atual
    LogFile* logFile;             // arquivo de log

   public:
    /**
     * @brief Construtor padrão da classe CPU.
     *
     */
    CPU() = default;

    /**
     * @brief Construtor parametrizado da classe CPU.
     *
     * Inicializa a fila de processos e a fila de prioridades, e define a política de escalonamento da CPU.
     * Por padrão, a CPU é inicializada como ociosa.
     *
     * @param politica Política de escalonamento do sistema. 0 - FCFS, 1 - SJF
     */
    CPU(bool politica, LogFile* log) : politica(politica), logFile(log) {
        queue = new Queue<Process*>();
        pq = new PriorityQueue<Process*>();
        busy = false;
    }

    /**
     * @brief Destrutor da classe CPU.
     *
     * Libera a memória alocada para a fila de processos e para a fila de prioridades.
     *
     */
    ~CPU() {
        delete queue;
        delete pq;
    }

    // getters e setters

    unsigned getCounter() const { return counter; }

    /**
     * @brief Verifica se a CPU está ocupada.
     *
     * @return True, se a CPU estiver ocupada. False, caso contrário.
     */
    bool isBusy() const { return busy; }

    /**
     * @brief Define se a CPU está ocupada.
     *
     * @param b True, se a CPU estiver ocupada. False, caso contrário.
     */
    void setBusy(bool b) { busy = b; }

    /**
     * @brief Retorna o processo que está sendo executado pela CPU.
     *
     * @return Ponteiro para o processo que está sendo executado pela CPU.
     */
    Process* getProcess() const { return process; }

    /**
     * @brief Função que recebe um processo e o insere na CPU. Se a CPU estiver ocupada,
     * o processo é inserido na fila de processos. Caso contrário, o processo é
     * inserido diretamente.
     *
     * @param p Ponteiro para o processo que será inserido.
     * @return True, se o processo foi inserido diretamente. False, caso o processo
     * tenha sido inserido na fila de processos.
     *
     */
    bool setProcess(Process* p) {
        if (!busy) {
            process = p;
            counter = p->getCPU();
            busy = true;
            logFile->directExecutionCPU(process->getId());
            concluded = false;
            return true;
        } else {
            if (politica) {
                pq->push(p->getCPU(), p);
            } else {
                queue->push(p);
            }
            logFile->loadIntoQueueCPU(p->getId());
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
                counter = process->getCPU();
                logFile->loadedFromQueueCPU(process->getId());
                concluded = false;
                return true;
            }
        } else {
            if (!queue->empty()) {
                process = queue->front();
                queue->pop();
                busy = true;
                counter = process->getCPU();
                logFile->loadedFromQueueCPU(process->getId());
                concluded = false;
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Função que executa o processo que está na CPU. Se o processo terminar de ser executado,
     * a CPU é liberada e o processo é retornado. Caso contrário, a CPU continua ocupada e a função
     * retorna nullptr.
     *
     * @return Ponteiro para o processo que terminou de ser executado. nullptr, caso o processo ainda
     * não tenha terminado de ser executado.
     */
    void execute() {
        counter--;
        if (!counter) concluded = true;
    }

    bool isConcluded() const { return concluded; }

    void removeProcess() {
        process = nullptr;
        busy = false;
        concluded = false;
    }
};

#endif
