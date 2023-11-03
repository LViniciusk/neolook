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
    /**
     * @brief Classe que representa um computador.
     *
     */
    Computer() = default;

    /**
     * @brief Classe que representa um computador.
     *
     */
    Computer(bool politica, Network* net) : politica(politica), network(net) {
        cpu = new CPU(politica);
        disk = new Disk[2]{Disk(politica), Disk(politica)};
    }

    /**
     * @brief Destrutor da classe Computer.
     *
     * Libera a memória alocada para o array de disco e imprime uma mensagem de
     * destruição do objeto.
     *
     */
    ~Computer() {
        delete[] disk;
        std::cout << "Computador destruido" << std::endl;
    }

    /**
     * @brief Retorna a CPU do computador.
     *
     * @return CPU& Referência para a CPU do computador.
     */
    CPU& getCPU() { return *cpu; }

    /**
     * @brief Retorna uma referência para o objeto Disk no índice especificado.
     *
     * @param i O índice do objeto Disk desejado.
     * @return Uma referência para o objeto Disk no índice especificado.
     */
    Disk& getDisk(int i) { return disk[i]; }
};

#endif