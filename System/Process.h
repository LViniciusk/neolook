/**
 * @file Process.h
 * @author Júnior Silva (junior.silva@alu.ufc.br) - 554222
 * @author Linyker Vinicius (botlink2030@alu.ufc.br) - 556280
 * @brief Struct que representa um processo.
 * @version 0.1
 * @date 06-11-2023
 *
 *
 */

#ifndef PROCESS_H
#define PROCESS_H

struct Process {
    unsigned id{};         // identificador do processo
    unsigned instant{};    // instante de chegada do processo
    unsigned d_cpu{};      // demanda de execução na CPU
    unsigned d_disk{};     // demanda de execução no disco
    unsigned d_network{};  // demanda de execução na rede

    /**
     * @brief Construtor padrão da classe Process.
     *
     */
    Process() = default;

    /**
     * @brief Construtor parametrizado da classe Process.
     *
     * @param id Identificador do processo.
     * @param instant Instante de chegada do processo.
     * @param d_cpu Demanda de execução na CPU.
     * @param d_disk Demanda de execução no disco.
     * @param d_network Demanda de execução na rede.
     */
    Process(unsigned id, unsigned instant, unsigned d_cpu, unsigned d_disk, unsigned d_network)
        : id(id), instant(instant), d_cpu(d_cpu), d_disk(d_disk), d_network(d_network) {}
};

#endif
