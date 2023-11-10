#include "../includes/Computer.h"

Computer::Computer() = default;

Computer::Computer(bool politica, Network* net, LogFile* logFile) : politica(politica), network(net) {
    cpu = new CPU(politica, logFile);
    disk = new Disk[2]{Disk(politica, logFile), Disk(politica, logFile)};
}

Computer::~Computer() {
    delete cpu;
    delete[] disk;
}

CPU& Computer::getCPU() { return *cpu; }

Disk& Computer::getDisk(int i) { return disk[i]; }
