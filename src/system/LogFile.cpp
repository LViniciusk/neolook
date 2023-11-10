#include "../includes/LogFile.h"

LogFile::LogFile(unsigned* time, bool detailed) : timer(time), detailed(detailed) {
    m_file = new std::ofstream(createLogArchiveName());
}

LogFile::~LogFile() {
    delete m_file;
}

std::string LogFile::createLogArchiveName() {
    // Criar o nome do arquivo
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::string filename = "tests/output/log_";
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

bool LogFile::isOpen() { return m_file->is_open(); }

void LogFile::executionCPU(const unsigned& processId) {
    if (!detailed) return;
    *m_file << "Time " << *timer << " - Processo " << processId
            << " carregado para execução na CPU" << std::endl;
}

void LogFile::executionCompletedCPU(const unsigned& processId) {
    if (!detailed) return;
    *m_file << "Time " << *timer << " - Processo " << processId
            << " finalizou execução na CPU" << std::endl;
}

void LogFile::executionDisk(const unsigned& processId) {
    if (!detailed) return;
    *m_file << "Time " << *timer << " - Processo " << processId
            << " carregado para execução no Disco" << std::endl;
}

void LogFile::loadedIntoQueue(const unsigned& processId) {
    if (!detailed) return;
    *m_file << "Time " << *timer << " - Processo " << processId
            << " carregado na fila de espera" << std::endl;
}

void LogFile::executionCompletedDisk(const unsigned& processId) {
    if (!detailed) return;
    *m_file << "Time " << *timer << " - Processo " << processId
            << " finalizou execução no Disco" << std::endl;
}

void LogFile::executionNetwork(const unsigned& processId) {
    if (!detailed) return;
    *m_file << "Time " << *timer << " - Processo " << processId
            << " carregado para execução na Rede" << std::endl;
}

void LogFile::executionCompletedNetwork(const unsigned& processId) {
    if (!detailed) return;
    *m_file << "Time " << *timer << " - Processo " << processId
            << " finalizou execução na Rede" << std::endl;
}

void LogFile::loadedFromQueue(const unsigned& processId) {
    if (!detailed) return;
    *m_file << "Time " << *timer << " - Processo " << processId
            << " resgatado da fila de espera" << std::endl;
}

void LogFile::processCreated(const unsigned& processId) {
    if (!detailed) return;
    *m_file << "Time " << *timer << " - Processo " << processId << " criado"
            << std::endl;
}

void LogFile::processFinished(const unsigned& processId) {
    if (!detailed) return;
    *m_file << "Time " << *timer << " - Processo " << processId
            << " finalizado" << std::endl;
}

void LogFile::headerMessage(const unsigned& qtdProcess,
                            const bool& politica,
                            const unsigned short& qtdPcs) {
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

void LogFile::executionCompleted() {
    *m_file << "\nSIMULAÇÃO ENCERRADA COM SUCESSO!\n"
            << std::endl;
}

void LogFile::statistics(unsigned long timer, double averageExecution,
                         double averageWaiting, double processingFee) {
    *m_file << "Estatísticas: -------------------------------------------------"
            << std::endl;
    *m_file << "Tempo total de execução   = " << timer << std::endl;
    *m_file << std::fixed << std::setprecision(2) << "Tempo médio de espera     = " << averageWaiting << std::endl;
    *m_file << std::fixed << std::setprecision(2) << "Tempo médio de execução   = " << averageExecution << std::endl;
    *m_file << std::fixed << std::setprecision(6) << "Taxa de processamento     = " << processingFee << std::endl;
    *m_file << "---------------------------------------------------------------";
}