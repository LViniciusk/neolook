#ifndef NETWORK_H
#define NETWORK_H

#include "../TAD'S/PriorityQueuePair.h"
#include "../TAD'S/Queue.h"
#include "Process.h"

class Network {
   private:
    Process process{};              // processo que esta sendo executado na rede
    Queue<Process> queue;           // fila de processos da rede
    PriorityQueuePair<Process> pq;  // fila de processos da rede
    bool politica;                  // politica de escalonamento. 0 - FCFS, 1 -
                                    // SJF
    bool busy;                      // indica se a rede está ocupada
    int time;                       // tempo de execução do processo atual

   public:
    Network() = default;

    Network(bool politica) : politica(politica) {
        queue = Queue<Process>();
        pq = PriorityQueuePair<Process>();
        busy = false;
    }

    ~Network() { std::cout << "Rede destruida" << std::endl; }

    // getters e setters
    /**
     * @brief Retorna o processo que esta sendo executado na rede
     *
     * @return Process*
     */
    Process& getProcess() { return process; }

    /**
     * @brief Seta um processo para ser executado na rede. Se a rede já estiver
     * ocupada, o processo é adicionado na fila de processos da rede.
     *
     * @param p Processo a ser executado na rede
     */
    void setProcess(Process& p) {
        if (!busy) {
            process = p;
            busy = true;
            time = 0;
        } else {
            if (politica)
                pq.push(p.getNetwork(), p);
            else
                queue.push(p);
        }
    }

    void setBusy(bool b) { busy = b; }

    void setTime() { time++; }

    int getTime() { return time; }

    bool isBusy() { return busy; }

    /**
     * @brief Função que imprime o estado atual da rede
     *
     */
    void print() {
        std::cout << "Rede: " << std::endl;
        std::cout << "\tEm execução: ";
        if (busy)
            process.print();
        else
            std::cout << "Nenhum processo em execução" << std::endl;
        std::cout << "\tFila: " << std::endl;
        if (politica) {
            if (pq.empty())
                std::cout << "\t\tFila vazia" << std::endl;
            else
                for (auto& p : pq) {
                    p.print();
                }
        } else {
            if (queue.empty())
                std::cout << "\t\tFila vazia" << std::endl;
            else
                for (auto& p : queue) {
                    p.print();
                }
        }
    }

    bool isConcluded() {
        if (!busy && queue.empty() && pq.empty()) return true;
    }

    void execute() {
        if (busy) {
            if (time == process.getNetwork()) {
                busy = false;
            } else {
                time++;
            }
        } else {
            if (politica) {
                if (!pq.empty()) {
                    process = pq.top();
                    pq.pop();
                    busy = true;
                    time = 0;
                }
            } else {
                if (!queue.empty()) {
                    process = queue.front();
                    queue.pop();
                    busy = true;
                    time = 0;
                }
            }
        }
    }
};

#endif  // NETWORK_H