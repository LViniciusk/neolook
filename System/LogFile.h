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
#include <string>

#include "Event.h"

/**
 * @brief Classe que representa o arquivo de log.
 *
 */
class LogFile {
   private:
    std::ofstream* m_file;  // ponteiro para o arquivo de log
    bool detailed;          // indica se o log é detalhado
    unsigned* timer;        // ponteiro para o timer do sistema

   public:
    /**
     * @brief Construtor padrão da classe LogFile.
     * Chama a função createLogArchiveName() para criar o nome do arquivo de log.
     * Cria o arquivo de log.
     *
     */
    LogFile(unsigned* timer, bool detailed) : detailed(detailed), timer(timer) {
        m_file = new std::ofstream(createLogArchiveName());
    }

    /**
     * @brief Destrutor da classe LogFile.
     *
     */
    ~LogFile() { m_file->close(); }

    /**
     * @brief Cria o nome do arquivo de log. O nome é composto pela data e hora da criação do arquivo.
     *
     * @return Uma string com o nome do arquivo de log.
     */
    std::string createLogArchiveName() {
        // Criar o nome do arquivo
        time_t now = time(0);
        tm* ltm = localtime(&now);
        std::string filename = "out/log_";
        filename += std::to_string(1900 + ltm->tm_year);
        filename += std::to_string(1 + ltm->tm_mon);
        filename += std::to_string(ltm->tm_mday);
        filename += "_";
        filename += std::to_string(ltm->tm_hour);
        filename += std::to_string(ltm->tm_min);
        filename += std::to_string(ltm->tm_sec);
        filename += ".txt";
        return filename;
    }

    /**
     * @brief Função que verifica se o arquivo de log está aberto.
     *
     * @return True, se o arquivo estiver aberto. False, caso contrário.
     */
    bool isOpen() { return m_file->is_open(); }

    // Messages for CPU --------------------------------------------------------

    /**
     * @brief Cria uma mensagem de carregamento direto do processo na CPU.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     * @param computerId Identificador do computador.
     */
    void directExecutionCPU(const int& processId) {
        if (!detailed) return;
        *m_file << "Time " << *timer << " - Processo " << processId
                << " carregado diretamente para execução na CPU" << std::endl;
    }

    /**
     * @brief Cria uma mensagem de carregamento do processo na fila de espera da CPU.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     * @param computerId Identificador do computador.
     */
    void loadIntoQueueCPU(const int& processId) {
        if (!detailed) return;
        *m_file << "Time " << *timer << " - Processo " << processId
                << " carregado na fila de espera da CPU" << std::endl;
    }

    /**
     * @brief Criar uma mensagem de finalização de execução do processo na CPU.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     * @param computerId Identificador do computador.
     */
    void executionCompletedCPU(const int& processId) {
        if (!detailed) return;
        *m_file << "Time " << *timer << " - Processo " << processId
                << " finalizou execução na CPU" << std::endl;
    }

    /**
     * @brief Cria uma mensagem de carregamento do processo da fila de espera para execução na CPU.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     * @param computerId Identificador do computador.
     */
    void loadedFromQueueCPU(const int& processId) {
        if (!detailed) return;
        *m_file << "Time " << *timer << " - Processo " << processId
                << " carregado da fila de espera para execução na CPU" << std::endl;
    }

    // Messages for Disk -------------------------------------------------------

    /**
     * @brief Cria uma mensagem de carregamento direto do processo no disco.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     * @param diskId Identificador do disco.
     * @param computerId Identificador do computador.
     */
    void directExecutionDisk(const int& processId) {
        if (!detailed) return;
        *m_file << "Time " << *timer << " - Processo " << processId
                << " carregado diretamente para execução no Disco" << std::endl;
    }

    /**
     * @brief Cria uma mensagem de carregamento do processo na fila de espera do disco.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     * @param diskId Identificador do disco.
     * @param computerId Identificador do computador.
     */
    void loadedIntoQueueDisk(const int& processId) {
        if (!detailed) return;
        *m_file << "Time " << *timer << " - Processo " << processId
                << " carregado na fila de espera do Disco" << std::endl;
    }

    /**
     * @brief Cria uma mensagem de finalização de execução do processo no disco.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     * @param diskId Identificador do disco.
     * @param computerId Identificador do computador.
     */
    void executionCompletedDisk(const int& processId) {
        if (!detailed) return;
        *m_file << "Time " << *timer << " - Processo " << processId
                << " finalizou execução no Disco" << std::endl;
    }

    /**
     * @brief Cria uma mensagem de carregamento do processo da fila de espera para execução no disco.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     * @param diskId Identificador do disco.
     * @param computerId Identificador do computador.
     */
    void loadFromQueueDisk(const int& processId) {
        if (!detailed) return;
        *m_file << "Time " << *timer << " - Processo " << processId
                << " carregado da fila de espera do Disco" << std::endl;
    }

    // Messages for Network ----------------------------------------------------

    /**
     * @brief Cria uma mensagem de carregamento direto do processo na rede.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     */
    void directExecutionNetwork(const int& processId) {
        if (!detailed) return;
        *m_file << "Time " << *timer << " - Processo " << processId
                << " carregado diretamente para execução na Rede" << std::endl;
    }

    /**
     * @brief Cria uma mensagem de carregamento do processo na fila de espera da rede.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     */
    void loadedIntoQueueNetwork(const int& processId) {
        if (!detailed) return;
        *m_file << "Time " << *timer << " - Processo " << processId
                << " carregado na fila de espera da Rede" << std::endl;
    }

    /**
     * @brief Cria uma mensagem de finalização de execução do processo na rede.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     */
    void executionCompletedNetwork(const int& processId) {
        if (!detailed) return;
        *m_file << "Time " << *timer << " - Processo " << processId
                << " finalizou execução na Rede" << std::endl;
    }

    /**
     * @brief Cria uma mensagem de carregamento do processo da fila de espera para execução na rede.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     */
    void loadFromQueueNetwork(const int& processId) {
        if (!detailed) return;
        *m_file << "Time " << *timer << " - Processo " << processId
                << " carregado da fila de espera para execução na Rede"
                << std::endl;
    }

    // Messages for Process ----------------------------------------------------

    /**
     * @brief Cria uma mensagem de criação do processo.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     */
    void processCreated(const int& processId) {
        if (!detailed) return;
        *m_file << "Time " << *timer << " - Processo " << processId << " criado" << std::endl;
    }

    /**
     * @brief Cria uma mensagem de finalização do processo.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     */
    void processFinished(const int processId) {
        if (!detailed) return;
        *m_file << "Time " << *timer << " - Processo " << processId << " finalizado" << std::endl;
    }

    // Standard messages -----------------------------------------------------

    /**
     * @brief Cria o cabeçalho do arquivo de log.
     *
     * @param qtdProcess Quantidade de processos.
     * @param politica Política de escalonamento.
     * @param qtdPcs Quantidade de computadores.
     */
    void headerMessage(int qtdProcess, bool politica, int qtdPcs) {
        *m_file << "LOG DE EXECUÇÃO ------------------------------------------"
                << std::endl;
        *m_file << "Quantidade de processos: " << qtdProcess << std::endl;
        *m_file << "Política de escalonamento: ";
        if (politica) {
            *m_file << "SJF" << std::endl;
        } else {
            *m_file << "FCFS" << std::endl;
        }
        *m_file << "Quantidade de computadores: " << qtdPcs << std::endl;
        *m_file << "----------------------------------------------------------\n\n";
    }

    /**
     * @brief Cria a mensagem de conclusão da simulação.
     *
     */
    void executionCompleted() {
        *m_file << "\nSIMULAÇÃO ENCERRADA COM SUCESSO!\n"
                << std::endl;
    }

    /**
     * @brief Cria a mensagem com as estatísticas da simulação.
     *
     * @param timer Tempo total de execução da simulação.
     * @param averageExecution Tempo médio de execução dos processos.
     * @param averageWaiting Tempo médio de espera dos processos.
     * @param processingFee Taxa de processamento.
     */
    void statistics(unsigned long timer, double averageExecution,
                    double averageWaiting, double processingFee) {
        *m_file << "Estatísticas: -------------------------------------------------"
                << std::endl;
        *m_file << "Tempo total de execução   = " << timer << std::endl;
        *m_file << "Tempo médio de espera     = " << averageWaiting << std::endl;
        *m_file << "Tempo médio de execução   = " << averageExecution << std::endl;
        *m_file << "Taxa de processamento     = " << processingFee << std::endl;
        *m_file << "---------------------------------------------------------------";
    }

    void createMessage(std::string message) {
        *m_file << message << std::endl;
    }
};

#endif  // LOGFILE_H