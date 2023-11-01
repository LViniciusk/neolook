#ifndef COMPUTER_H
#define COMPUTER_H

#include <iostream>

#include "CPU.h"
#include "Disk.h"
#include "Process.h"

template <typename Type>
class Computer {
   private:
    CPU<Type> cpu;     // CPU do computador
    Disk<Type>* disk;  // Discos do computador

   public:
    Queue<Process> processos;  // para fins de teste

    Computer() {
        disk = new Disk<Type>[2];
        processos = Queue<Process>();
    }

    void print() {
        std::cout << "Computador: " << std::endl;
        std::cout << "\tCPU: " << std::endl;
        cpu.print();
        std::cout << "\tDisco 1: " << std::endl;
        disk[0].print();
        std::cout << "\tDisco 2: " << std::endl;
        disk[1].print();
    }

    void receiveProcess(Process p) { processos.push(p); }
};

#endif