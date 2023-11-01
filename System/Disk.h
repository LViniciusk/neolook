#ifndef DISK_H
#define DISK_H

#include "Process.h"

template <typename Type>
class Disk {
   private:
    Process* process{};  // processo que está sendo executado no disco
    Type queue;          // fila de processos do disco

   public:
    Disk() { queue = Type(); }

    // getters e setters

    /**
     * @brief Retorna o processo que está sendo executado no disco
     *
     * @return Process*
     */
    Process* getProcess() { return process; }

    /**
     * @brief Seta um processo para ser executado no disco. Se o disco já
     * estiver ocupado, o processo é adicionado na fila de processos do disco.
     *
     * @param p Processo a ser executado no disco
     */
    void setProcess(Process* p) { process = p; }

    /**
     * @brief Função que imprime o estado atual do disco
     *
     */
    void print() {
        std::cout << "Disco: " << std::endl;
        std::cout << "\tEm execução: ";
        if (process != nullptr)
            process->print();
        else
            std::cout << "Nenhum processo em execução" << std::endl;

        std::cout << "\tFila: " << std::endl;
        for (auto& p : queue) p.print();
    }

    ~Disk() { delete process; }
};

#endif  // DISK_H