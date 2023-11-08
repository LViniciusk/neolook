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

/**
 * @brief Estrutura que representa um evento.
 *
 */
struct Event {
    unsigned id{};             // identificador do processo.
    bool concluded{};          // indica se o processo foi concluído.
    unsigned tempoEspera{};    // tempo de espera do processo.
    unsigned tempoExecucao{};  // tempo de execução do processo.
    unsigned instanteFinal{};  // instante de término do processo.
};

#endif  // EVENT_H
