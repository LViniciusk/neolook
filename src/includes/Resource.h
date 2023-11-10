#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>

#include "../tads/PriorityQueue.h"
#include "../tads/Queue.h"
#include "LogFile.h"
#include "Process.h"

class Resource {
   protected:
    Process* process;             // processo que está sendo executado na CPU
    Queue<Process*>* queue;       // fila de processos da CPU
    PriorityQueue<Process*>* pq;  // fila de processos da CPU
    bool politica;                // politica de escalonamento. 0 - FCFS, 1 - SJF
    bool busy;                    // indica se a CPU está ocupada
    LogFile* logFile;             // arquivo de log
    unsigned short counter;       // contador de tempo

   private:
   public:
    /**
     * @brief Construct a new Resource object
     *
     */
    Resource();

    /**
     * @brief Construct a new Resource object
     *
     * @param politica
     * @param logFile
     */
    Resource(bool politica, LogFile* logFile);

    /**
     * @brief Destroy the Resource object
     *
     */
    virtual ~Resource();

    /**
     * @brief Verifica se a CPU está ocupada
     *
     * @return true
     * @return false
     */
    bool isBusy() const;

    /**
     * @brief Retorna o processo que está sendo executado na CPU
     *
     * @return Process*
     */
    Process* getProcess() const;

    /**
     * @brief Carrega um processo na CPU da fila de processos
     *
     */
    virtual void loadFromQueue();

    /**
     * @brief Executa o processo que está na CPU em um ciclo
     *
     */
    virtual void execute();

    /**
     * @brief Verifica se o processo que está na CPU terminou sua execução
     *
     * @return true
     * @return false
     */
    virtual bool isFinished();

    /**
     * @brief Remove o processo que está na CPU
     *
     */
    virtual void finishProcess();

    /**
     * @brief Escolhe se o processo será executado na CPU ou inserido na fila de processos
     *
     * @param p
     */
    virtual void setProcess(Process* p) = 0;
};

class CPU : public Resource {
   public:
    CPU();

    CPU(bool politica, LogFile* logFile);

    ~CPU();

    void setProcess(Process* p) override;
};

class Disk : public Resource {
   public:
    Disk();

    Disk(bool politica, LogFile* logFile);

    ~Disk();

    void setProcess(Process* p) override;
};

class Network : public Resource {
   public:
    Network();

    Network(bool politica, LogFile* logFile);

    ~Network();

    void setProcess(Process* p) override;
};

#endif  // RESOURCE_H