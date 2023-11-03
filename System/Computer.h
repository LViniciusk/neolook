#ifndef COMPUTER_H
#define COMPUTER_H

#include <iostream>

#include "CPU.h"
#include "Disk.h"
#include "Network.h"
#include "Process.h"

class Computer {
   private:
    CPU cpu;           // CPU do computador
    Disk* disk;        // Discos do computador
    bool politica;     // politica de escalonamento da CPU. 0 - FCFS, 1 - SJF
    Network* network;  // rede do computador

   public:
    Computer() = default;

    Computer(bool politica, Network* net) : politica(politica), network(net) {
        cpu = CPU(politica);
        disk = new Disk[2]{Disk(politica), Disk(politica)};
    }

    ~Computer() {
        delete[] disk;
        std::cout << "Computador destruido" << std::endl;
    }

    void print() {
        std::cout << "CPU: ";
        if (politica) {
            PriorityQueuePair<Process> pq = cpu.getPriorityQueue();
            for (auto& p : pq) {
                std::cout << "Process - " << p.getInstant() << " - "
                          << p.getCPU() << " - " << p.getDisk() << " - "
                          << p.getNetwork() << "\n";
            }
        } else {
            Queue<Process> queue = cpu.getQueue();
            for (auto& p : queue) {
                std::cout << "Process - " << p.getInstant() << " - "
                          << p.getCPU() << " - " << p.getDisk() << " - "
                          << p.getNetwork() << "\n";
            }
        }
    }

    void insertCPU(Process& p) { cpu.setProcess(p); }

    void removeCPU() {
        cpu.setBusy(false);  // libera a CPU
        // agora escolhe aleatoriamente um disco para executar o processo
        int i = rand() % 2;
        insertDisk(cpu.getProcess(), i);
    }

    void insertDisk(Process& p, int i) { disk[i].setProcess(p); }

    Process& removeDisk(int i) {
        disk[i].setBusy(false);  // libera o disco
        return disk[i].getProcess();
    }

    void execute() {
        cpu.execute();
        if (cpu.getProcess().getCPU() == cpu.getTime()) {
            removeCPU();
        }
        for (int i = 0; i < 2; i++) {
            disk[i].execute();
            if (disk[i].getProcess().getDisk() == disk[i].getTime()) {
                network->setProcess(removeDisk(i));
            }
        }
    }

    CPU& getCPU() { return cpu; }

    Disk& getDisk(int i) { return disk[i]; }
};

#endif