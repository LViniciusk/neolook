#ifndef PROCESS_H
#define PROCESS_H

/**
 * @brief Classe que representa um processo.
 *
 */
class Process {
   private:
    unsigned id{};                  // identificador do processo
    int instant;                    // instante de início do processo.
    int d_cpu;                      // demanda de CPU do processo.
    int d_disk;                     // demanda de disco do processo.
    int d_network;                  // demanda de rede do processo.
    bool executado{};               // indica se o processo já foi executado.
    unsigned long tempoEspera{};    // tempo médio de espera do processo.
    unsigned long tempoExecucao{};  // tempo médio de execução do processo.
    unsigned long instanteCPU{};    // instante que foi enviado para a CPU.
    unsigned long instanteDisco{};  // instante que foi enviado para o disco.
    unsigned long instanteRede{};   // instante que foi enviado para a rede.
    unsigned long instanteFinal{};  // instante de término do processo.

   public:
    /**
     * @brief Construct a new Process object
     *
     */
    Process() = default;

    /**
     * @brief Construtor da classe Process.
     *
     * @param start Instante de início do processo
     * @param cpu Demanda de CPU do processo
     * @param disk Demanda de disco do processo
     * @param rede Demanda de rede do processo
     */
    Process(unsigned id, int start, int cpu, int disk, int rede)
        : id(id), instant(start), d_cpu(cpu), d_disk(disk), d_network(rede) {
        tempoExecucao = cpu + disk + rede;
        executado = false;
    }

    /**
     * @brief Destrutor da classe Process.
     *
     */
    ~Process() = default;

    // getters e setters
    /**
     * @brief Retorna o identificador do processo.
     *
     * @return unsigned
     */
    unsigned getId() const { return id; }

    /**
     * @brief Retorna o instante de início do processo.
     *
     * @return int
     */
    int getInstant() const { return instant; }

    /**
     * @brief Retorna a demanda de CPU do processo.
     *
     * @return int
     */
    int getCPU() const { return d_cpu; }

    /**
     * @brief Retorna a demanda de disco do processo.
     *
     * @return int
     */
    int getDisk() const { return d_disk; }

    /**
     * @brief Retorna a demanda de rede do processo.
     *
     * @return int
     */
    int getNetwork() const { return d_network; }

    /**
     * @brief Retorna se o processo já foi executado.
     *
     * @return true
     * @return false
     */
    bool getExecutado() const { return executado; }

    /**
     * @brief Seta se o processo já foi executado.
     *
     * @param e true se o processo já foi executado, false caso contrário.
     */
    void setExecutado(bool e) { executado = e; }

    /**
     * @brief Retorna o tempo total de espera do processo.
     *
     * @return unsigned long
     */
    unsigned long getTempoEspera() const { return tempoEspera; }

    /**
     * @brief Seta o tempo total de espera do processo.
     *
     * @param time Tempo médio de espera do processo.
     */
    void setTempoEspera(const unsigned long& time) { tempoEspera = time; }

    /**
     * @brief Retorna o tempo total de execução do processo.
     *
     * @return unsigned long
     */
    unsigned long getTempoExecucao() const { return tempoExecucao; }

    /**
     * @brief Retorna o instante que o processo foi enviado para ser executado
     * na CPU.
     *
     * @return unsigned long
     */
    unsigned long getInstanteCPU() const { return instanteCPU; }

    /**
     * @brief Retorna o instante que o processo foi enviado para ser executado
     * no disco.
     *
     * @return unsigned long
     */
    unsigned long getInstanteDisco() const { return instanteDisco; }

    /**
     * @brief Retorrna o instante que o processo foi enviado para ser executado
     * na rede.
     *
     * @return unsigned long
     */
    unsigned long getInstanteRede() const { return instanteRede; }

    /**
     * @brief Retorna o instante de término do processo.
     *
     * @return unsigned long
     */
    unsigned long getInstanteFinal() const { return instanteFinal; }

    /**
     * @brief Seta o instante que o processo foi enviado para ser executado na
     * CPU. Incrementa o tempo de espera e o tempo de execução do processo.
     *
     * @param time Instante que o processo foi enviado para ser executado na CPU
     */
    void setInstanteCPU(const unsigned long& time) {
        instanteCPU = time;
        tempoEspera += time - instant;
    }

    /**
     * @brief Seta o instante que o processo foi enviado para ser executado no
     * disco. Incrementa o tempo de espera e o tempo de execução do processo.
     *
     * @param time Instante que o processo foi enviado para ser executado no
     * disco
     */
    void setInstanteDisco(const unsigned long& time) {
        instanteDisco = time;
        tempoEspera += time - (instanteCPU + d_cpu);
    }

    /**
     * @brief Seta o instante que o processo foi enviado para ser executado na
     * rede. Incrementa o tempo de espera e o tempo de execução do processo.
     *
     * @param time Instante que o processo foi enviado para ser executado na
     * rede
     */
    void setInstanteRede(const unsigned long& time) {
        instanteRede = time;
        tempoEspera += time - (instanteDisco + d_disk);
        tempoExecucao += tempoEspera;
    }

    /**
     * @brief Seta o instante de término do processo.
     *
     * @param time Instante de término do processo
     */
    void setInstanteFinal(const unsigned long& time) { instanteFinal = time; }

    /**
     * @brief Função que imprime os dados do processo.
     *
     */
    void print() {
        std::cout << "Process - ";
        std::cout << std::setw(5) << id << " - ";
        std::cout << std::setw(5) << instant << " - ";
        std::cout << std::setw(5) << d_cpu << " - ";
        std::cout << std::setw(5) << d_disk << " - ";
        std::cout << std::setw(5) << d_network << " - ";
        std::cout << std::setw(5) << instanteFinal << " - ";
        std::cout << std::setw(2) << executado << " - ";
        std::cout << std::setw(5) << tempoEspera << " - ";
        std::cout << std::setw(5) << tempoExecucao << "\n";
    }
};

#endif