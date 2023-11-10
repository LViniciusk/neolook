#include "../includes/Resource.h"
Resource::Resource() = default;

Resource::Resource(bool politica, LogFile* logFile) : politica(politica), logFile(logFile) {
    queue = new Queue<Process*>();
    pq = new PriorityQueue<Process*>();
    busy = false;
}

Resource::~Resource() {
    delete queue;
    delete pq;
}

bool Resource::isBusy() const { return busy; }

Process* Resource::getProcess() const { return process; }

void Resource::loadFromQueue() {
    switch (politica) {
        case 0:
            if (!queue->empty()) {
                setProcess(queue->front());
                queue->pop();
                busy = true;
            }
            break;
        case 1:
            if (!pq->empty()) {
                setProcess(pq->top());
                pq->pop();
                busy = true;
            }
            break;
            logFile->loadedFromQueue(process->id);
    }
}

void Resource::execute() {
    // decrementa o contador de tempo
    if (counter > 0) {
        counter--;
    }
}

bool Resource::isFinished() {
    return counter == 0 && process != nullptr;
}

void Resource::finishProcess() {
    busy = false;
    logFile->processFinished(process->id);
    process = nullptr;
}

CPU::CPU() = default;

CPU::CPU(bool politica, LogFile* logFile) : Resource(politica, logFile) {}

CPU::~CPU() = default;

void CPU::setProcess(Process* p) {
    if (!busy) {
        process = p;
        busy = true;
        counter = p->d_cpu;
        logFile->executionCPU(p->id);
    } else {
        switch (politica) {
            case 0:
                queue->push(p);
                break;
            case 1:
                pq->push(p->d_cpu, p);
                break;
        }
        logFile->loadedIntoQueue(p->id);
    }
}

Disk::Disk() = default;

Disk::Disk(bool politica, LogFile* logFile) : Resource(politica, logFile) {}

Disk::~Disk() = default;

void Disk::setProcess(Process* p) {
    if (!busy) {
        process = p;
        busy = true;
        counter = p->d_disk;
        logFile->executionDisk(p->id);
    } else {
        switch (politica) {
            case 0:
                queue->push(p);
                break;
            case 1:
                pq->push(p->d_disk, p);
                break;
        }
        logFile->loadedIntoQueue(p->id);
    }
}

Network::Network() = default;

Network::Network(bool politica, LogFile* logFile) : Resource(politica, logFile) {}

Network::~Network() = default;

void Network::setProcess(Process* p) {
    if (!busy) {
        process = p;
        busy = true;
        counter = p->d_network;
        logFile->executionNetwork(p->id);
    } else {
        if (politica) {
            pq->push(p->d_network, p);
        } else {
            queue->push(p);
        }
        logFile->loadedIntoQueue(p->id);
    }
}