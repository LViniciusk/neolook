/**
 * @file Computer.h
 * @author Júnior Silva (junior.silva@alu.ufc.br) - 554222
 * @author Linyker Vinicius (botlink2030@alu.ufc.br) - 556280
 * @brief Classe que representa um computador.
 * @version 0.1
 * @date 06-11-2023
 *
 *
 */

#ifndef COMPUTER_H
#define COMPUTER_H

#include <iostream>

#include "LogFile.h"
#include "Process.h"
#include "Resouce.h"

/**
 * @brief Classe que representa um computador.
 *
 */
class Computer {
   private:
    CPU* cpu;          // CPU do computador
    Disk* disk;        // Discos do computador
    bool politica;     // politica de escalonamento da CPU. 0 - FCFS, 1 - SJF
    Network* network;  // rede do computador

   public:
    /**
     * @brief Construtor padrão da classe Computer.
     *
     */
    Computer() = default;

    /**
     * @brief Construtor parametrizado da classe Computer.
     * Cria a CPU e os discos do computador.
     *
     * @param politica Política de escalonamento da CPU. 0 - FCFS, 1 - SJF
     * @param net Rede do computador.
     * @param log Arquivo de log.
     */
    Computer(bool politica, Network* net, LogFile* log) : politica(politica), network(net) {
        cpu = new CPU(politica, log);
        disk = new Disk[2]{Disk(politica, log), Disk(politica, log)};
    }

    /**
     * @brief Destrutor da classe Computer.
     *
     * Libera a memória alocada para o array de disco e para a CPU.
     *
     */
    ~Computer() {
        delete[] disk;
        delete cpu;
    }

    /**
     * @brief Retorna a CPU do computador.
     *
     * @return Referência para a CPU do computador.
     */
    CPU& getCPU() { return *cpu; }

    /**
     * @brief Retorna uma referência para o objeto Disk no índice especificado.
     *
     * @param i O índice do objeto Disk desejado.
     * @return Uma referência para o objeto Disk no índice especificado.
     */
    Disk& getDisk(unsigned short i) { return disk[i]; }
};

#endif
