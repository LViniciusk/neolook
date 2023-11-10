#include "../includes/System.h"
System::System(unsigned short qPcs, bool pol, bool printLog) : qPcs(qPcs), politica(pol), printLog(printLog) {
    logFile = new LogFile(&timer, printLog);
    processos = new Vector<Process>();
    network = new Network(politica, logFile);
    computers = Vector<Computer*>();
    for (unsigned short i = 0; i < qPcs; i++) {
        computers.push_back(new Computer(politica, network, logFile));
    }
}

System::~System() {
    for (unsigned short i = 0; i < qPcs; i++) {
        delete computers[i];
    }
    delete network;
    delete processos;
    delete logFile;
}

void System::loadFile(std::string arq) {
    std::ifstream file(arq);
    unsigned id{}, instant{};
    unsigned short cpu{}, disk{}, network{};
    while (file >> instant >> cpu >> disk >> network) {
        processos->push_back(Process(id++, instant, cpu, disk, network));
    }
    qtdProcessos = processos->size();
    file.close();
}

void System::execute() {
    unsigned pendentes = qtdProcessos;
    // std::srand(time(NULL));
    std::srand(123);
    Vector<Process>::iterator it = processos->begin();
    Vector<Process>::iterator end = processos->end();
    logFile->headerMessage(pendentes, politica, qPcs);

    while (true) {
        // CARREGA OS PROCESSOS NA CPU ----------------------------
        while (it != end && it->instant == timer) {
            int pc = rand() % qPcs;
            computers[pc]->getCPU().setProcess(&(*it));
            it++;
        }

        for (unsigned i = 0; i < qPcs; i++) {
            // CPU ------------------------------------------------
            CPU& cpu = computers[i]->getCPU();
            if (cpu.isFinished()) {
                Process* p = cpu.getProcess();
                cpu.finishProcess();
                int disk = rand() % 2;
                computers[i]->getDisk(disk).setProcess(p);
                cpu.loadFromQueue();
            }
            cpu.execute();
            // DISCOS  --------------------------------------------
            for (unsigned j = 0; j < 2; j++) {
                Disk& disk = computers[i]->getDisk(j);
                if (disk.isFinished()) {
                    Process* p = disk.getProcess();
                    disk.finishProcess();
                    network->setProcess(p);
                    disk.loadFromQueue();
                }
                disk.execute();
            }
        }

        // REDE ---------------------------------------------------
        if (network->isFinished()) {
            Process* p = network->getProcess();
            network->finishProcess();
            unsigned tempoExecucao = timer - p->instant;
            unsigned tempoEspera = tempoExecucao - (p->d_cpu + p->d_disk + p->d_network);
            tempoMedioExecucao += (double)tempoExecucao / qtdProcessos;
            tempoMedioEspera += (double)tempoEspera / qtdProcessos;
            network->loadFromQueue();
            pendentes--;
            if (pendentes == 0) break;
        }
        network->execute();

        timer++;  // incrementa o relógio lógico
    }
    taxaProcessamento = (double)qtdProcessos / (timer - processos->begin()->instant);
    std::cout << "Política de escalonamento = " << (politica ? "SJF" : "FCFS") << std::endl;
    std::cout << "Quantidade de processos   = " << qtdProcessos << std::endl;
    std::cout << "Tempo total de execução   = " << timer << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "Tempo médio de espera     = " << tempoMedioEspera << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "Tempo médio de execução   = " << tempoMedioExecucao << std::endl;
    std::cout << std::fixed << std::setprecision(6) << "Taxa de processamento     = " << taxaProcessamento << std::endl
              << std::endl;
    logFile->executionCompleted();
    logFile->statistics(timer, tempoMedioExecucao, tempoMedioEspera, taxaProcessamento);
}
