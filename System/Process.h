/**
 * @file Process.h
 * @author Júnior Silva (junior.silva@alu.ufc.br) - 554222
 * @author Linyker Vinicius (botlink2030@alu.ufc.br) - 556280
 * @brief Classe que representa um processo.
 * @version 0.1
 * @date 06-11-2023
 *
 *
 */

#ifndef PROCESS_H
#define PROCESS_H

class Process {
   private:
    unsigned id{};       // identificador do processo
    unsigned instant{};  // instante de chegada do processo
    unsigned cpu{};      // demanda de execução na CPU
    unsigned disk{};     // demanda de execução no disco
    unsigned network{};  // demanda de execução na rede

   public:
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
     * @param cpu Demanda de tempo de execução do processo na CPU.
     * @param disk Demanda de tempo de execução do processo no disco.
     * @param network Demanda de tempo de execução do processo na rede.
     */
    Process(unsigned id, unsigned instant, unsigned cpu, unsigned disk, unsigned network)
        : id(id), instant(instant), cpu(cpu), disk(disk), network(network) {}

    /**
     * @brief Destrutor da classe Process.
     *
     */
    ~Process() = default;

    // getters e setters

    /**
     * @brief Retorna o identificador do processo. Este índice é único para cada processo, e
     * representa o índice do processo no vetor de processos do sistema.
     *
     * @return Identificador do processo.
     */
    unsigned getId() { return id; }

    /**
     * @brief Retorna o instante de chegada do processo.
     *
     * @return Instante de chegada do processo.
     */
    unsigned getInstant() { return instant; }

    /**
     * @brief Retorna a demanda de execução do processo na CPU.
     *
     * @return Demanda de execução do processo na CPU.
     */
    unsigned getCPU() { return cpu; }

    /**
     * @brief Retorna a demanda de execução do processo no disco.
     *
     * @return Demanda de execução do processo no disco.
     */
    unsigned getDisk() { return disk; }

    /**
     * @brief Retorna a demanda de execução do processo na rede.
     *
     * @return Demanda de execução do processo na rede.
     */
    unsigned getNetwork() { return network; }
};

#endif
