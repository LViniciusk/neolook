#ifndef CPU_H
#define CPU_H

#include <iostream>

#include "Process.h"

template <typename Type>
class CPU {
   private:
    Process* process{};  // processo que está sendo executado na CPU
    Type queue;          // fila de processos da CPU

   public:
    CPU() { queue = Type(); }

    // getters e setters

    /**
     * @brief Retorna o processo que está sendo executado na CPU
     *
     * @return Process*
     */
    Process* getProcess() { return process; }

    /**
     * @brief Seta o processo que está sendo executado na CPU. Se a CPU já
     * estiver ocupada, o processo é adicionado na fila de processos da CPU.
     *
     * @param p Processo a ser executado na CPU
     */
    void setProcess(Process* p) {
        if (process == nullptr) {
            process = p;
        } else {
            queue.push(*p);
        }
    }

    /**
     * @brief Função que imprime o estado atual da CPU
     *
     */
    void print() {
        std::cout << "\tEm execução: ";
        if (process != nullptr)
            process->print();
        else
            std::cout << "Nenhum processo em execução" << std::endl;

        std::cout << "\tFila: " << std::endl;
        for (auto& p : queue) p.print();
    }
};

#endif