#ifndef PROCESS_H
#define PROCESS_H

class Process
{
    public:
    int d_start;
    int d_cpu;
    int d_disk;
    int d_rede;

    Process() = default;

    Process(int start, int cpu, int disk, int rede)
    {
        d_start = start;
        d_cpu = cpu;
        d_disk = disk;
        d_rede = rede;
    }

};

#endif