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
    Resource();

    Resource(bool politica, LogFile* logFile);

    virtual ~Resource();

    bool isBusy() const;

    Process* getProcess() const;

    virtual void loadFromQueue();

    virtual void execute();

    virtual bool isFinished();

    virtual void finishProcess();

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