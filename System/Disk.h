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
#include "LogFile.h"
#include "Process.h"

/**
 * @brief Classe que representa um Disco do computador.
 *
 */
class Disk {
   private:
    Process* process{};           // processo que está sendo executado no disco
    Queue<Process*>* queue;       // fila de processos do disco
    PriorityQueue<Process*>* pq;  // fila de processos do disco
    bool politica;                // politica de escalonamento. 0 - FCFS, 1 - SJF
    bool busy;                    // indica se o disco está ocupado
    bool concluded{false};        // indica se o processo terminou de ser executado
    unsigned counter;             // tempo de execução do processo atual
    LogFile* logFile;             // arquivo de log

   public:
    /**
     * @brief Construtor parametrizado da classe Disk.
     *
     * Inicializa a fila de processos e a fila de prioridades, e define a política de escalonamento do Disco.
     * Por padrão, o Disco é inicializado como ocioso.
     *
     * @param politica Política de escalonamento do sistema. 0 - FCFS, 1 - SJF
     */
    Disk(bool politica, LogFile* log) : politica(politica), logFile(log) {
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

    /**
     * @brief Verifica se o disco está ocupada.
     *
     * @return True, se o disco estiver ocupado. False, caso contrário.
     */
    bool isBusy() const { return busy; }

    unsigned getCounter() const { return counter; }

    /**
     * @brief Define se o disco está ocupado.
     *
     * @param b True, se o disco estiver ocupado. False, caso contrário.
     */
    void setBusy(bool b) { busy = b; }

    /**
     * @brief Retorna o processo que está sendo executado pelo disco.
     *
     * @return Ponteiro para o processo que está sendo executado pelo disco.
     */
    Process* getProcess() const { return process; }

    /**
     * @brief Função que recebe um processo e o insere no disco. Se o disco estiver ocupado,
     * o processo é inserido na fila de processos. Caso contrário, o processo é
     * inserido diretamente no disco para ser executado.
     *
     * @param p Ponteiro para o processo que será inserido.
     * @return True, se o processo foi inserido diretamente. False, caso o processo
     * tenha sido inserido na fila de processos.
     *
     */
    bool setProcess(Process* p) {
        if (!busy) {
            process = p;
            counter = p->getDisk();
            busy = true;
            logFile->directExecutionDisk(p->getId());
            concluded = false;
            return true;
        } else {
            if (politica) {
                pq->push(p->getDisk(), p);
            } else {
                queue->push(p);
            }
            logFile->loadedIntoQueueDisk(p->getId());
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
                counter = process->getDisk();
                logFile->loadFromQueueDisk(process->getId());
                concluded = false;
                return true;
            }
        } else {
            if (!queue->empty()) {
                process = queue->front();
                queue->pop();
                busy = true;
                counter = process->getDisk();
                logFile->loadFromQueueDisk(process->getId());
                concluded = false;
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Função que executa o processo que está no disco. Se o processo terminar de ser executado,
     * o disco é liberado e o processo é retornado. Caso contrário, o disco continua ocupado e a função
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

#endif  // DISK_H
