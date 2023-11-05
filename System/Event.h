#ifndef EVENT_H
#define EVENT_H

#include <iomanip>
#include <iostream>

#include "Process.h"

class Event {
   public:
    Process* process;               // processo associado ao evento.
    bool concluded{};               // indica se o processo foi concluído.
    unsigned long tempoEspera{};    // tempo de espera do processo.
    unsigned long tempoExecucao{};  // tempo de execução do processo.
    unsigned long instanteCPU{};    // instante que foi enviado para a CPU.
    unsigned long instanteDisco{};  // instante que foi enviado para o disco.
    unsigned long instanteRede{};   // instante que foi enviado para a rede.
    unsigned long instanteFinal{};  // instante de término do processo.

    Event() = default;

    /**
     * @brief Construtor do struct Event.
     *
     * @param id Identificador do evento
     * @param process Processo associado ao evento
     */
    Event(Process* process) {
        this->process = process;
        tempoExecucao =
            (process->getCPU() + process->getDisk() + process->getNetwork());
    }

    /**
     * @brief Destrutor do struct Event.
     *
     */
    ~Event() { delete process; }

    /**
     * @brief Incrementa o tempo de espera do processo num certo recurso.
     *
     * @param time
     */
    void addTempoEspera(const unsigned long& time) {
        tempoEspera += time;
        tempoExecucao += time;
    }

    void setInstanteCPU(const unsigned long& time) {
        instanteCPU = time;
        addTempoEspera(time - process->getInstant());
    }
    void setInstanteDisco(const unsigned long& time) {
        instanteDisco = time;
        addTempoEspera(time - process->getInstant());
    }
    void setInstanteRede(const unsigned long& time) {
        instanteRede = time;
        addTempoEspera(time - process->getInstant());
    }

    void print() {
        std::cout << std::setw(7) << process->getId() << " - ";
        std::cout << std::setw(5) << process->getInstant() << " - ";
        std::cout << std::setw(5) << process->getCPU() << " - ";
        std::cout << std::setw(5) << process->getDisk() << " - ";
        std::cout << std::setw(5) << process->getNetwork() << " - ";
        std::cout << std::setw(7) << instanteFinal << " - ";
        std::cout << std::setw(2) << concluded << " - ";
        std::cout << std::setw(7) << tempoEspera << " - ";
        std::cout << std::setw(7) << tempoExecucao << "\n";
    }
};

#endif  // EVENT_H