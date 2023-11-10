/**
 * @file LogFile.h
 * @author Júnior Silva (junior.silva@alu.ufc.br) - 554222
 * @author Linyker Vinicius (botlink2030@alu.ufc.br) - 556280
 * @brief Classe que representa o arquivo de log.
 * @version 0.1
 * @date 06-11-2023
 *
 *
 */

#ifndef LOGFILE_H
#define LOGFILE_H

#include <ctime>
#include <fstream>
#include <iomanip>
#include <string>

/**
 * @brief Classe que representa o arquivo de log.
 *
 */
class LogFile {
   private:
    std::ofstream* m_file;  // ponteiro para o arquivo de log
    unsigned* timer;        // tempo atual do sistema
    bool detailed{};        // indica se o log é detalhado

   public:
    /**
     * @brief Construtor padrão da classe LogFile.
     * Chama a função createLogArchiveName() para criar o nome do arquivo de log.
     * Cria o arquivo de log.
     *
     */
    LogFile(unsigned* time, bool detailed);

    /**
     * @brief Destrutor da classe LogFile.
     *
     */
    ~LogFile();

    /**
     * @brief Cria o nome do arquivo de log. O nome é composto pela data e hora da criação do arquivo.
     *
     * @return Uma string com o nome do arquivo de log.
     */
    std::string createLogArchiveName();

    /**
     * @brief Função que verifica se o arquivo de log está aberto.
     *
     * @return True, se o arquivo estiver aberto. False, caso contrário.
     */
    bool isOpen();

    // Messages for CPU --------------------------------------------------------

    /**
     * @brief Cria uma mensagem de carregamento direto do processo na CPU.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     * @param computerId Identificador do computador.
     */
    void executionCPU(const unsigned& processId);

    /**
     * @brief Criar uma mensagem de finalização de execução do processo na CPU.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     * @param computerId Identificador do computador.
     */
    void executionCompletedCPU(const unsigned& processId);

    // Messages for Disk -------------------------------------------------------

    /**
     * @brief Cria uma mensagem de carregamento direto do processo no disco.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     * @param diskId Identificador do disco.
     * @param computerId Identificador do computador.
     */
    void executionDisk(const unsigned& processId);

    /**
     * @brief Cria uma mensagem de carregamento do processo na fila de espera do disco.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     * @param diskId Identificador do disco.
     * @param computerId Identificador do computador.
     */
    void loadedIntoQueue(const unsigned& processId);

    /**
     * @brief Cria uma mensagem de finalização de execução do processo no disco.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     * @param diskId Identificador do disco.
     * @param computerId Identificador do computador.
     */
    void executionCompletedDisk(const unsigned& processId);

    // Messages for Network ----------------------------------------------------

    /**
     * @brief Cria uma mensagem de carregamento direto do processo na rede.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     */
    void executionNetwork(const unsigned& processId);

    /**
     * @brief Cria uma mensagem de finalização de execução do processo na rede.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     */
    void executionCompletedNetwork(const unsigned& processId);

    /**
     * @brief Cria uma mensagem de carregamento do processo da fila de espera para execução na rede.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     */
    void loadedFromQueue(const unsigned& processId);

    // Messages for Process ----------------------------------------------------

    /**
     * @brief Cria uma mensagem de criação do processo.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     */
    void processCreated(const unsigned& processId);

    /**
     * @brief Cria uma mensagem de finalização do processo.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     */
    void processFinished(const unsigned& processId);

    // Standard messages -----------------------------------------------------

    /**
     * @brief Cria o cabeçalho do arquivo de log.
     *
     * @param qtdProcess Quantidade de processos.
     * @param politica Política de escalonamento.
     * @param qtdPcs Quantidade de computadores.
     */
    void headerMessage(const unsigned& qtdProcess,
                       const bool& politica,
                       const unsigned short& qtdPcs);

    /**
     * @brief Cria a mensagem de conclusão da simulação.
     *
     */
    void executionCompleted();

    /**
     * @brief Cria a mensagem com as estatísticas da simulação.
     *
     * @param timer Tempo total de execução da simulação.
     * @param averageExecution Tempo médio de execução dos processos.
     * @param averageWaiting Tempo médio de espera dos processos.
     * @param processingFee Taxa de processamento.
     */
    void statistics(unsigned long timer, double averageExecution,
                    double averageWaiting, double processingFee);
};

#endif  // LOGFILE_H