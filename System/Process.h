#ifndef PROCESS_H
#define PROCESS_H

class Process {
   private:
    int instant;
    int d_cpu;
    int d_disk;
    int d_network;
    bool executado;

   public:
    Process() = default;

    Process(int start, int cpu, int disk, int rede)
        : instant(start), d_cpu(cpu), d_disk(disk), d_network(rede) {
        executado = false;
    }

    ~Process() {
        std::cout << "Processo " << getInstant() << " destruido" << std::endl;
    }

    // getters e setters
    int getInstant() const { return instant; }
    int getCPU() const { return d_cpu; }
    int getDisk() const { return d_disk; }
    int getNetwork() const { return d_network; }

    void print() {
        std::cout << "Processo: " << std::endl;
        std::cout << "\tInício: " << instant << std::endl;
        std::cout << "\tCPU: " << d_cpu << std::endl;
        std::cout << "\tDisco: " << d_disk << std::endl;
        std::cout << "\tRede: " << d_network << std::endl;
    }
};

#endif