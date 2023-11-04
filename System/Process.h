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
    unsigned id{};                 // identificador do processo
    int instant;                   // instante de início do processo.
    int d_cpu;                     // demanda de CPU do processo.
    int d_disk;                    // demanda de disco do processo.
    int d_network;                 // demanda de rede do processo.
    bool executado{};              // indica se o processo já foi executado.
    long long tempoEspera{};       // tempo médio de espera do processo.
    long long tempoExecucao{};     // tempo médio de execução do processo.
    long long instanteCPU{};       // instante que foi enviado para a CPU.
    long long instanteDisco{};     // instante que foi enviado para o disco.
    long long instanteRede{};      // instante que foi enviado para a rede.
    long long tempoEsperaCPU{};    // tempo de espera na CPU.
    long long tempoEsperaDisco{};  // tempo de espera no disco.
    long long tempoEsperaRede{};   // tempo de espera na rede.
    long long instanteFinal{};     // instante de término do processo.

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
    void setExecutado(bool e) {
        executado = e;
        calculaTempos();
    }
    long long getTempoEspera() const { return tempoEspera; }
    void setTempoEspera(const long long& time) { tempoEspera = time; }
    long long getTempoExecucao() const { return tempoExecucao; }
    long long getInstanteCPU() const { return instanteCPU; }
    long long getInstanteDisco() const { return instanteDisco; }
    long long getInstanteRede() const { return instanteRede; }
    long long getTempoEsperaCPU() const { return tempoEsperaCPU; }
    long long getTempoEsperaDisco() const { return tempoEsperaDisco; }
    long long getTempoEsperaRede() const { return tempoEsperaRede; }
    long long getInstanteFinal() const { return instanteFinal; }

    void setInstanteCPU(const long long& time) {
        instanteCPU = time;
        tempoEsperaCPU = instanteCPU - instant;
    }

    void setInstanteDisco(const long long& time) {
        instanteDisco = time;
        tempoEsperaDisco = time - (instanteCPU + d_cpu);
    }

    void setInstanteRede(const long long& time) {
        instanteRede = time;
        tempoEsperaRede = time - (instanteDisco + d_disk);
    }

    void setInstanteFinal(const long long& time) { instanteFinal = time; }

    void calculaTempos() {
        tempoEspera = tempoEsperaCPU + tempoEsperaDisco + tempoEsperaRede;
        tempoExecucao = instanteFinal - instant;
    }
};

#endif