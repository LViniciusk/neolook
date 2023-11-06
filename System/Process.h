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
    int id{};       // identificador do processo
    int instant{};  // instante de chegada do processo
    int cpu{};      // tempo de execução na CPU
    int disk{};     // tempo de execução no disco
    int network{};  // tempo de execução na rede

   public:
    /**
     * @brief Classe que representa um processo.
     *
     */
    Process() = default;

    /**
     * @brief Construtor da classe Process.
     *
     * @param id Identificador do processo
     * @param instant Instante de chegada do processo
     * @param cpu Tempo de execução na CPU
     * @param disk Tempo de execução no disco
     * @param network Tempo de execução na rede
     */
    Process(int id, int instant, int cpu, int disk, int network)
        : id(id), instant(instant), cpu(cpu), disk(disk), network(network) {}

    /**
     * @brief Destrutor da classe Process.
     *
     */
    ~Process() = default;

    // getters e setters

    /**
     * @brief Retorna o identificador do processo.
     *
     * @return int Identificador do processo.
     */
    int getId() { return id; }

    /**
     * @brief Retorna o instante de chegada do processo.
     *
     * @return int Instante de chegada do processo.
     */
    int getInstant() { return instant; }

    /**
     * @brief Retorna o tempo de execução do processo na CPU.
     *
     * @return int Tempo de execução do processo na CPU.
     */
    int getCPU() { return cpu; }

    /**
     * @brief Retorna o tempo de execução do processo no disco.
     *
     * @return int Tempo de execução do processo no disco.
     */
    int getDisk() { return disk; }

    /**
     * @brief Retorna o tempo de execução do processo na rede.
     *
     * @return int Tempo de execução do processo na rede.
     */
    int getNetwork() { return network; }

    void print() {
        std::cout << "Processo " << id << " - Instante: " << instant
                  << " - CPU: " << cpu << " - Disco: " << disk
                  << " - Rede: " << network << std::endl;
    }
};

#endif