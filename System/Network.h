#ifndef NETWORK_H
#define NETWORK_H

#include "Process.h"

template <typename Type>
class Network {
   private:
    Process* process{};  // processo que esta sendo executado na rede
    Type networkQueue;   // fila de processos da rede

   public:
    Network() {
        process = nullptr;
        networkQueue = Type();
    }

    ~Network() { delete process; }

    // getters e setters
    /**
     * @brief Retorna o processo que esta sendo executado na rede
     *
     * @return Process*
     */
    Process* getProcess() { return process; }

    /**
     * @brief Seta um processo para ser executado na rede. Se a rede já estiver
     * ocupada, o processo é adicionado na fila de processos da rede.
     *
     * @param p Processo a ser executado na rede
     */
    void setProcess(Process* p) { process = p; }

    /**
     * @brief Função que imprime o estado atual da rede
     *
     */
    void print() {
        std::cout << "Rede: " << std::endl;
        std::cout << "\tEm execução: ";
        if (process != nullptr)
            process->print();
        else
            std::cout << "Nenhum processo em execução" << std::endl;
        std::cout << "\tFila: " << std::endl;
        for (auto& p : networkQueue) p->print();
    }
};

#endif  // NETWORK_H