/**
 * @file Process.h
 * @author Júnior Silva (junior.silva@alu.ufc.br) - 554222
 * @author Linyker Vinicius (botlink2030@alu.ufc.br) - 556280
 * @brief Estrutura que representa um processo.
 * @version 0.1
 * @date 06-11-2023
 *
 *
 */

#ifndef PROCESS_H
#define PROCESS_H

struct Process {
    unsigned id{};               // identificador do processo
    unsigned instant{};          // instante de chegada do processo
    unsigned short d_cpu{};      // demanda de execução na CPU
    unsigned short d_disk{};     // demanda de execução no disco
    unsigned short d_network{};  // demanda de execução na rede

    Process(const unsigned& id,
            const unsigned& instant,
            const unsigned short& d_cpu,
            const unsigned short& d_disk,
            const unsigned short& d_network);

    Process();

    ~Process();
};

#endif
