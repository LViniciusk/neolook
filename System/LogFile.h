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

class LogFile {
   private:
    // Arquivo de log, deve permanecer aberto durante toda a execucao
    std::ofstream* m_file;

   public:
    LogFile() {
        // abre o arquivo de log
        m_file = new std::ofstream(createLogArchiveName());
    }

    ~LogFile() { m_file->close(); }

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

    bool isOpen() { return m_file->is_open(); }

    // Messages for CPU --------------------------------------------------------

    void directExecutionCPU(unsigned long time, int processId, int computerId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " carregado diretamente para execução na CPU do Computador "
                << computerId << std::endl;
    }

    void loadIntoQueueCPU(unsigned long time, int processId, int computerId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " carregado na fila de espera da CPU do Computador "
                << computerId << std::endl;
    }

    void executionCompletedCPU(unsigned long time, int processId,
                               int computerId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " finalizou execução na CPU do Computador " << computerId
                << std::endl;
    }

    void loadedFromQueueCPU(unsigned long time, int processId, int computerId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " carregado da fila de espera para execução na CPU do "
                   "Computador "
                << computerId << std::endl;
    }

    // Messages for Disk -------------------------------------------------------

    void directExecutionDisk(unsigned long time, int processId, int diskId,
                             int computerId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " carregado diretamente para execução no Disco " << diskId
                << " do Computador " << computerId << std::endl;
    }

    void loadedIntoQueueDisk(unsigned long time, int processId, int diskId,
                             int computerId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " carregado na fila de espera do Disco " << diskId
                << " do Computador " << computerId << std::endl;
    }

    void executionCompletedDisk(unsigned long time, int processId, int diskId,
                                int computerId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " finalizou execução no Disco " << diskId
                << " do Computador " << computerId << std::endl;
    }

    void loadFromQueueDisk(unsigned long time, int processId, int diskId,
                           int computerId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " carregado da fila de espera do Disco " << diskId
                << " para execução no Computador " << computerId << std::endl;
    }

    // Messages for Network ----------------------------------------------------

    void directExecutionNetwork(unsigned long time, int processId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " carregado diretamente para execução na Rede" << std::endl;
    }

    void loadedIntoQueueNetwork(unsigned long time, int processId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " carregado na fila de espera da Rede" << std::endl;
    }

    void executionCompletedNetwork(unsigned long time, int processId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " finalizou execução na Rede" << std::endl;
    }

    void loadFromQueueNetwork(unsigned long time, int processId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " carregado da fila de espera para execução na Rede"
                << std::endl;
    }

    // Messages for Process ----------------------------------------------------

    void processCreated(unsigned long time, int processId) {
        *m_file << "Time " << time << " - Processo " << processId << " criado"
                << std::endl;
    }

    void processFinished(unsigned long time, int processId) {
        *m_file << "Time " << time << " - Processo " << processId
                << " finalizado" << std::endl;
    }

    // Standard messages -----------------------------------------------------

    void headerMessage(int qtdProcess, bool politica, int qtdPcs) {
        *m_file << "LOG DE EXECUÇÃO -------------------------------------"
                << std::endl;
        *m_file << "Quantidade de processos: " << qtdProcess << std::endl;
        *m_file << "Política de escalonamento: ";
        if (politica) {
            *m_file << "SJF" << std::endl;
        } else {
            *m_file << "FCFS" << std::endl;
        }
        *m_file << "Quantidade de computadores: " << qtdPcs << std::endl;
        *m_file << "-----------------------------------------------------\n\n";
    }

    void executionCompleted() {
        *m_file << "\nSIMULAÇÃO ENCERRADA COM SUCESSO!\n"
                << std::endl;
    }

    void statistics(unsigned long timer, double averageExecution,
                    double averageWaiting, double processingFee) {
        *m_file << "Estatísticas: ---------------------------------------"
                << std::endl;
        *m_file << "Tempo total de execução: " << timer << std::endl;
        *m_file << "Tempo médio de espera: " << averageWaiting << std::endl;
        *m_file << "Tempo médio de execução: " << averageExecution << std::endl;
        *m_file << "Taxa de processamento: " << processingFee << std::endl;
        *m_file << "-----------------------------------------------------";
    }
};

#endif  // LOGFILE_H