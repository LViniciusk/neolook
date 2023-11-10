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

#include "Process.h"
#include "Resource.h"

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
    Computer();

    /**
     * @brief Construtor parametrizado da classe Computer.
     *
     * @param politica Política de escalonamento da CPU. 0 - FCFS, 1 - SJF
     * @param net Ponteiro para a rede do computador.
     */
    Computer(bool politica, Network* net, LogFile* logFile);

    /**
     * @brief Destrutor da classe Computer.
     *
     * Libera a memória alocada para o array de disco.
     *
     */
    ~Computer();

    /**
     * @brief Retorna a CPU do computador.
     *
     * @return Referência para a CPU do computador.
     */
    CPU& getCPU();

    /**
     * @brief Retorna uma referência para o objeto Disk no índice especificado.
     *
     * @param i O índice do objeto Disk desejado.
     * @return Uma referência para o objeto Disk no índice especificado.
     */
    Disk& getDisk(int i);
};

#endif
