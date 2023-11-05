#ifndef PROCESS_H
#define PROCESS_H

// Tempo médio de execução: o tempo de execução de um processo inclui não
// somente os tempos de processamento em cada recurso, mas também os tempos de
// espera em cada fila de cada recurso.

// Tempo médio de espera: o tempo de espera de um processo consiste na soma dos
// tempos de espera em cada fila de cada recurso. Você deve contabilizar os
// tempos de espera de cada processo simulado e, ao final, calcular a média.

// Taxa de processamento: taxa de processamento consiste na razão do número
// total de processos executados pelo intervalo de tempo decorrente desde o
// início do primeiro processo até o término do último. Logo, se o primeiro
// processo foi iniciado no instante t1 e o n-ésimo (último) foi finalizado no
// instante t2, a taxa de processamento é calculada como n/(t2 − t1).

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
     * @brief Destroy the Process object
     *
     */
    ~Process() = default;

    // getters e setters
    unsigned getId() const { return id; }
    int getInstant() const { return instant; }
    int getCPU() const { return d_cpu; }
    int getDisk() const { return d_disk; }
    int getNetwork() const { return d_network; }
    bool getExecutado() const { return executado; }
    void setExecutado(bool e) { executado = e; }
    unsigned long getTempoEspera() const { return tempoEspera; }
    void setTempoEspera(const unsigned long& time) { tempoEspera = time; }
    unsigned long getTempoExecucao() const { return tempoExecucao; }
    unsigned long getInstanteCPU() const { return instanteCPU; }
    unsigned long getInstanteDisco() const { return instanteDisco; }
    unsigned long getInstanteRede() const { return instanteRede; }
    unsigned long getInstanteFinal() const { return instanteFinal; }

    void setInstanteCPU(const unsigned long& time) {
        instanteCPU = time;
        tempoEspera += time - instant;
        tempoExecucao += tempoEspera;
    }

    void setInstanteDisco(const unsigned long& time) {
        instanteDisco = time;
        tempoEspera += time - (instanteCPU + d_cpu);
        tempoExecucao += tempoEspera;
    }

    void setInstanteRede(const unsigned long& time) {
        instanteRede = time;
        tempoEspera += time - (instanteDisco + d_disk);
        tempoExecucao += tempoEspera;
    }

    void setInstanteFinal(const unsigned long& time) { instanteFinal = time; }
};

#endif