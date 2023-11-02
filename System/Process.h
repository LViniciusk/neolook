#ifndef PROCESS_H
#define PROCESS_H

class Process {
   private:
    int d_start;
    int d_cpu;
    int d_disk;
    int d_rede;

   public:
    Process() = default;

    Process(int start, int cpu, int disk, int rede) {
        d_start = start;
        d_cpu = cpu;
        d_disk = disk;
        d_rede = rede;
    }

    // getters e setters
    int getStart() const { return d_start; }
    int getCPU() const { return d_cpu; }
    int getDisk() const { return d_disk; }
    int getRede() const { return d_rede; }

    void print() {
        std::cout << "Processo: " << std::endl;
        std::cout << "\tInício: " << d_start << std::endl;
        std::cout << "\tCPU: " << d_cpu << std::endl;
        std::cout << "\tDisco: " << d_disk << std::endl;
        std::cout << "\tRede: " << d_rede << std::endl;
    }

    Process operator*(const Process& p) {
        Process temp;
        temp.d_start = d_start * p.d_start;
        temp.d_cpu = d_cpu * p.d_cpu;
        temp.d_disk = d_disk * p.d_disk;
        temp.d_rede = d_rede * p.d_rede;
        return temp;
    }
};

#endif