#ifndef PROCESS_H
#define PROCESS_H

class Process
{
    public:
    int d_cpu;
    int d_disk;
    int d_rede;

    Process() = default;

    Process(int cpu, int disk, int rede)
    {
        d_cpu = cpu;
        d_disk = disk;
        d_rede = rede;
    }

};

#endif