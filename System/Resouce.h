#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>

#include "../TAD'S/PriorityQueue.h"
#include "../TAD'S/Queue.h"
#include "LogFile.h"
#include "Process.h"

/**
 * @brief Classe que representa um recurso.
 * É uma classe abstrata.
 * As classes CPU, Disk e Network herdam de Resource.
 *
 */
class Resource {
   protected:
    Process* process;             // processo que está sendo executado na CPU
    Queue<Process*>* queue;       // fila de processos da CPU
    PriorityQueue<Process*>* pq;  // fila de processos da CPU
    bool politica;                // politica de escalonamento. 0 - FCFS, 1 - SJF
    bool busy;                    // indica se a CPU está ocupada
    bool concluded{false};        // indica se o processo terminou de ser executado
    unsigned counter;             // tempo de execução do processo atual
    LogFile* logFile;             // arquivo de log

    /**
     * @brief Função que carrega um processo da fila da CPU.
     *
     */
    void especificLoadQueue() {
        process = queue->front();
        queue->pop();
        busy = true;
    }

    /**
     * @brief Função que carrega um processo da fila de prioridade da CPU.
     *
     */
    void especificLoadPQ() {
        process = pq->top();
        pq->pop();
        busy = true;
    }

   public:
    /**
     * @brief Construtor padrão da classe Resource.
     *
     */
    Resource() = default;

    /**
     * @brief Construtor parametrizado da classe Resource.
     *
     * Inicializa a fila de processos e a fila de prioridades, e define a política de escalonamento do recurso.
     * Por padrão, o recurso é inicializado como ocioso.
     *
     * @param politica Política de escalonamento do sistema. 0 - FCFS, 1 - SJF
     */
    Resource(bool& politica, LogFile* log) : politica(politica), logFile(log) {
        queue = new Queue<Process*>();
        pq = new PriorityQueue<Process*>();
        busy = false;
    }

    /**
     * @brief Destrutor da classe Resource.
     *
     * Libera a memória alocada para a fila de processos e para a fila de prioridades.
     *
     */
    ~Resource() {
        delete queue;
        delete pq;
    }

    /**
     * @brief Verifica se o recurso está ocupado.
     *
     * @return True, se o recurso estiver ocupado. False, caso contrário.
     */
    const bool& isBusy() const { return busy; }

    /**
     * @brief Retorna o tempo de execução do processo atual.
     *
     * @return Tempo de execução do processo atual.
     */
    const unsigned& getCounter() const { return counter; }

    /**
     * @brief Retorna o processo que está sendo executado no recurso.
     *
     * @return Processo que está sendo executado
     * no recurso.
     */
    Process* getProcess() const { return process; }

    /**
     * @brief Define se o recurso está ocupado.
     *
     * @param b True, se o recurso estiver ocupado. False, caso contrário.
     */
    void setBusy(bool& b) { busy = b; }

    const bool& isConcluded() const { return concluded; }

    void removeProcess() {
        process = nullptr;
        busy = false;
        concluded = false;
    }

    void execute() {
        if (busy && counter > 0) --counter;
        if (counter == 0) concluded = true;
    }
};

/**
 * @brief Classe que representa a CPU.
 * Herda de Resource.
 *
 */
class CPU : public Resource {
   public:
    /**
     * @brief Construtor padrão da classe CPU.
     *
     */
    CPU() = default;

    /**
     * @brief Construtor parametrizado da classe CPU.
     * Inicializa a fila de processos e a fila de prioridades, e define a política de escalonamento da CPU.
     * Por padrão, a CPU é inicializada como ociosa.
     *
     * @param politica Política de escalonamento do sistema. 0 - FCFS, 1 - SJF
     * @param log Arquivo de log.
     */
    CPU(bool& politica, LogFile* log) : Resource(politica, log) {}

    /**
     * @brief Função que insere um processo na CPU.
     * Se a CPU estiver ociosa, o processo é inserido diretamente na CPU.
     * Caso contrário, o processo é inserido na fila de processos da CPU.
     *
     * @param p Processo a ser inserido na CPU.
     */
    void setProcess(Process* p) {
        if (!busy) {
            process = p;
            busy = true;
            concluded = false;
            counter = p->d_cpu;
            // logFile->directExecutionCPU(p->id);
        } else {
            switch (politica) {
                case 0:
                    pq->push(p->d_cpu, p);
                    break;
                case 1:
                    queue->push(p);
                    break;
            }
            // logFile->loadIntoQueueCPU(p->id);
        }
    }

    /**
     * @brief Função que carrega um processo da fila de processos da CPU.
     *
     */
    void loadFromQueue() {
        switch (politica) {
            case 0:
                if (!pq->empty()) {
                    especificLoadPQ();
                    // logFile->loadedFromQueueCPU(process->id);
                    busy = true;
                    concluded = false;
                    counter = process->d_cpu;
                }
                break;
            case 1:
                if (!queue->empty()) {
                    especificLoadQueue();
                    // logFile->loadedFromQueueCPU(process->id);
                    busy = true;
                    concluded = false;
                    counter = process->d_cpu;
                }
                break;
        }
    }
};

/**
 * @brief Classe que representa um disco.
 * Herda de Resource.
 *
 */
class Disk : public Resource {
   public:
    // construtor padrão
    Disk() = default;

    /**
     * @brief Construtor parametrizado da classe Disk.
     * Inicializa a fila de processos e a fila de prioridades, e define a política de escalonamento do disco.
     * Por padrão, o disco é inicializado como ocioso.
     *
     * @param politica Política de escalonamento do sistema. 0 - FCFS, 1 - SJF
     * @param log Arquivo de log.
     */
    Disk(bool& politica, LogFile* log) : Resource(politica, log) {}

    /**
     * @brief Função que insere um processo no disco.
     * Se o disco estiver ocioso, o processo é inserido diretamente no disco.
     * Caso contrário, o processo é inserido na fila de processos do disco.
     *
     * @param p Processo a ser inserido no disco.
     */
    void setProcess(Process* p) {
        if (!busy) {
            process = p;
            busy = true;
            concluded = false;
            counter = p->d_disk;
            // logFile->directExecutionDisk(p->id);
        } else {
            switch (politica) {
                case 0:
                    pq->push(p->d_disk, p);
                    break;
                case 1:
                    queue->push(p);
                    break;
            }
            // logFile->loadedIntoQueueDisk(p->id);
        }
    }

    /**
     * @brief Função que carrega um processo da fila de processos do disco.
     *
     */
    void loadFromQueue() {
        switch (politica) {
            case 0:
                if (!pq->empty()) {
                    especificLoadPQ();
                    // logFile->loadFromQueueDisk(process->id);
                    busy = true;
                    concluded = false;
                    counter = process->d_disk;
                }
                break;
            case 1:
                if (!queue->empty()) {
                    especificLoadQueue();
                    // logFile->loadFromQueueDisk(process->id);
                    busy = true;
                    concluded = false;
                    counter = process->d_disk;
                }
                break;
        }
    }
};

/**
 * @brief Classe que representa a rede.
 * Herda de Resource.
 *
 */
class Network : public Resource {
   public:
    // construtor padrão
    Network() = default;

    /**
     * @brief Construtor parametrizado da classe Network.
     * Inicializa a fila de processos e a fila de prioridades, e define a política de escalonamento da rede.
     * Por padrão, a rede é inicializada como ociosa.
     *
     * @param politica Política de escalonamento do sistema. 0 - FCFS, 1 - SJF
     * @param log Arquivo de log.
     */
    Network(bool& politica, LogFile* log) : Resource(politica, log) {}

    /**
     * @brief Função que insere um processo na rede.
     * Se a rede estiver ociosa, o processo é inserido diretamente na rede.
     * Caso contrário, o processo é inserido na fila de processos da rede.
     *
     * @param p Processo a ser inserido na rede.
     */
    void setProcess(Process* p) {
        if (!busy) {
            process = p;
            busy = true;
            concluded = false;
            counter = p->d_network;
            // logFile->directExecutionNetwork(p->id);
        } else {
            switch (politica) {
                case 0:
                    pq->push(p->d_network, p);
                    break;
                case 1:
                    queue->push(p);
                    break;
            }
            // logFile->loadedIntoQueueNetwork(p->id);
        }
    }

    /**
     * @brief Função que carrega um processo da fila de processos da rede.
     *
     */
    void loadFromQueue() {
        switch (politica) {
            case 0:
                if (!pq->empty()) {
                    especificLoadPQ();
                    // logFile->loadFromQueueNetwork(process->id);
                    busy = true;
                    concluded = false;
                    counter = process->d_network;
                }
                break;
            case 1:
                if (!queue->empty()) {
                    especificLoadQueue();
                    // logFile->loadFromQueueNetwork(process->id);
                    busy = true;
                    concluded = false;
                    counter = process->d_network;
                }
                break;
        }
    }
};

#endif  // RESOURCE_H