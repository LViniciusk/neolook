#ifndef COMPUTER_H
#define COMPUTER_H

#include <iostream>

#include "CPU.h"
#include "Disk.h"
#include "Network.h"
#include "Process.h"

class Computer {
   private:
    CPU* cpu;          // CPU do computador
    Disk* disk;        // Discos do computador
    bool politica;     // politica de escalonamento da CPU. 0 - FCFS, 1 - SJF
    Network* network;  // rede do computador

   public:
    Computer() = default;

    Computer(bool politica, Network* net) : politica(politica), network(net) {
        cpu = new CPU(politica);
        disk = new Disk[2]{Disk(politica), Disk(politica)};
    }

    ~Computer() {
        delete[] disk;
        std::cout << "Computador destruido" << std::endl;
    }

    CPU& getCPU() { return *cpu; }

    Disk& getDisk(int i) { return disk[i]; }
};

#endif