#ifndef COMPUTER_H
#define COMPUTER_H

#include "Process.h"
#include <iostream>

template <typename Type>
class Computer
{
public:
    Type CPU;
    Type Disk[2];

    void receiveProcess(Process p)
    {
        CPU.push(p.d_cpu);
        if((Disk[0].empty() && Disk[1].empty()) || (!Disk[0].empty() && !Disk[1].empty())){
            Disk[rand() % 2].push(p.d_disk);
        }else if(Disk[0].empty()){
            Disk[0].push(p.d_disk);
        }else{
            Disk[1].push(p.d_disk);
        }
    }

    void print()
    {
        std::cout << "    CPU: " << CPU.size() << std::endl;
        std::cout << "    Disk1: " << Disk[0].size() << std::endl;
        std::cout << "    Disk2: " << Disk[1].size() << "\n\n";
    }
};

#endif