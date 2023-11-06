/**
 * @file Event.h
 * @author Júnior Silva (junior.silva@alu.ufc.br) - 554222
 * @author Linyker Vinicius (botlink2030@alu.ufc.br) - 556280
 * @brief Estrutura que representa um evento.
 * @version 0.1
 * @date 06-11-2023
 *
 *
 */

#ifndef EVENT_H
#define EVENT_H

#include <iomanip>
#include <iostream>

struct Event {
    int id{};                       // identificador do processo.
    bool concluded{};               // indica se o processo foi concluído.
    unsigned long tempoEspera{};    // tempo de espera do processo.
    unsigned long tempoExecucao{};  // tempo de execução do processo.
    unsigned long instanteCPU{};    // instante que foi enviado para a CPU.
    unsigned long instanteDisco{};  // instante que foi enviado para o disco.
    unsigned long instanteRede{};   // instante que foi enviado para a rede.
    unsigned long instanteFinal{};  // instante de término do processo.
};

#endif  // EVENT_H