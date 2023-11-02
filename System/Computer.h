#ifndef COMPUTER_H
#define COMPUTER_H

#include <iostream>

#include "CPU.h"
#include "Disk.h"
#include "Process.h"

class Computer {
   private:
    CPU* cpu;       // CPU do computador
    Disk* disk;     // Discos do computador
    bool politica;  // politica de escalonamento da CPU. 0 - FCFS, 1 - SJF

   public:
    Queue<Process> processos;  // para fins de teste

    Computer() = default;

    Computer(bool politica) : politica(politica) {
        disk = new Disk[2]{Disk(politica), Disk(politica)};
        cpu = new CPU(politica);
    }

    ~Computer() {
        delete[] disk;
        delete cpu;
    }

    void print() {
        std::cout << "CPU: ";
        cpu->print();
        std::cout << "Disco 1: ";
        disk[0].print();
        std::cout << "Disco 2: ";
        disk[1].print();
    }

    void receiveProcess(Process& p) { cpu->setProcess(p); }
};

#endif