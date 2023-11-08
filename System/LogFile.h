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

   public:
    /**
     * @brief Construtor padrão da classe LogFile.
     * Chama a função createLogArchiveName() para criar o nome do arquivo de log.
     * Cria o arquivo de log.
     *
     */
    LogFile() {
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
    bool isOpen() const { return m_file->is_open(); }

    // Messages for CPU --------------------------------------------------------

    /**
     * @brief Cria uma mensagem de carregamento direto do processo na CPU.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     * @param computerId Identificador do computador.
     */
    void directExecutionCPU(unsigned long time, int processId, int computerId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " carregado diretamente para execução na CPU do Computador "
                << computerId << std::endl;
    }

    /**
     * @brief Cria uma mensagem de carregamento do processo na fila de espera da CPU.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     * @param computerId Identificador do computador.
     */
    void loadIntoQueueCPU(unsigned long time, int processId, int computerId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " carregado na fila de espera da CPU do Computador "
                << computerId << std::endl;
    }

    /**
     * @brief Criar uma mensagem de finalização de execução do processo na CPU.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     * @param computerId Identificador do computador.
     */
    void executionCompletedCPU(unsigned long time, int processId,
                               int computerId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " finalizou execução na CPU do Computador " << computerId
                << std::endl;
    }

    /**
     * @brief Cria uma mensagem de carregamento do processo da fila de espera para execução na CPU.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     * @param computerId Identificador do computador.
     */
    void loadedFromQueueCPU(unsigned long time, int processId, int computerId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " carregado da fila de espera para execução na CPU do "
                   "Computador "
                << computerId << std::endl;
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
    void directExecutionDisk(unsigned long time, int processId, int diskId,
                             int computerId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " carregado diretamente para execução no Disco " << diskId
                << " do Computador " << computerId << std::endl;
    }

    /**
     * @brief Cria uma mensagem de carregamento do processo na fila de espera do disco.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     * @param diskId Identificador do disco.
     * @param computerId Identificador do computador.
     */
    void loadedIntoQueueDisk(unsigned long time, int processId, int diskId,
                             int computerId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " carregado na fila de espera do Disco " << diskId
                << " do Computador " << computerId << std::endl;
    }

    /**
     * @brief Cria uma mensagem de finalização de execução do processo no disco.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     * @param diskId Identificador do disco.
     * @param computerId Identificador do computador.
     */
    void executionCompletedDisk(unsigned long time, int processId, int diskId,
                                int computerId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " finalizou execução no Disco " << diskId
                << " do Computador " << computerId << std::endl;
    }

    /**
     * @brief Cria uma mensagem de carregamento do processo da fila de espera para execução no disco.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     * @param diskId Identificador do disco.
     * @param computerId Identificador do computador.
     */
    void loadFromQueueDisk(unsigned long time, int processId, int diskId,
                           int computerId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " carregado da fila de espera do Disco " << diskId
                << " para execução no Computador " << computerId << std::endl;
    }

    // Messages for Network ----------------------------------------------------

    /**
     * @brief Cria uma mensagem de carregamento direto do processo na rede.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     */
    void directExecutionNetwork(unsigned long time, int processId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " carregado diretamente para execução na Rede" << std::endl;
    }

    /**
     * @brief Cria uma mensagem de carregamento do processo na fila de espera da rede.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     */
    void loadedIntoQueueNetwork(unsigned long time, int processId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " carregado na fila de espera da Rede" << std::endl;
    }

    /**
     * @brief Cria uma mensagem de finalização de execução do processo na rede.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     */
    void executionCompletedNetwork(unsigned long time, int processId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " finalizou execução na Rede" << std::endl;
    }

    /**
     * @brief Cria uma mensagem de carregamento do processo da fila de espera para execução na rede.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     */
    void loadFromQueueNetwork(unsigned long time, int processId) {
        *m_file << "Time " << time << " - Processo " << processId
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
    void processCreated(unsigned long time, int processId) {
        *m_file << "Time " << time << " - Processo " << processId << " criado"
                << std::endl;
    }

    /**
     * @brief Cria uma mensagem de finalização do processo.
     *
     * @param time Tempo atual da simulação.
     * @param processId Identificador do processo.
     */
    void processFinished(unsigned long time, int processId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " finalizado" << std::endl;
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
};

#endif  // LOGFILE_H