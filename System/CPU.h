#ifndef CPU_H
#define CPU_H

#include <iostream>

#include "../TAD'S/PriorityQueuePair.h"
#include "../TAD'S/Queue.h"
#include "Process.h"

class CPU {
   private:
    Process process{};              // processo que está sendo executado na CPU
    Queue<Process> queue;           // fila de processos da CPU
    PriorityQueuePair<Process> pq;  // fila de processos da CPU
    bool politica;  // politica de escalonamento. 0 - FCFS, 1 - SJF
    bool busy;      // indica se a CPU está ocupada
    int time;       // tempo de execução do processo atual

   public:
    CPU() = default;

    CPU(bool politica) : politica(politica) {
        queue = Queue<Process>();
        pq = PriorityQueuePair<Process>();
        busy = false;
        std::cout << "\tCPU criada" << std::endl;
    }

    ~CPU() { std::cout << "CPU destruida" << std::endl; }

    // getters e setters

    /**
     * @brief Retorna o processo que está sendo executado na CPU
     *
     * @return Process*
     */
    Process& getProcess() { return process; }

    /**
     * @brief Retorna a fila de processos da CPU
     *
     * @return Queue<Process>*
     */
    Queue<Process>& getQueue() { return queue; }

    /**
     * @brief Retorna a fila de processos da CPU
     *
     * @return PriorityQueuePair<Process>*
     */
    PriorityQueuePair<Process>& getPriorityQueue() { return pq; }

    /**
     * @brief Seta o processo que está sendo executado na CPU. Se a CPU já
     * estiver ocupada, o processo é adicionado na fila de processos da CPU.
     *
     * @param p Processo a ser executado na CPU
     */
    void setProcess(Process& p) {
        if (!busy) {
            process = p;
            time = 0;
            busy = true;
            std::cout << "\t\tProcesso inserido na CPU" << std::endl;
        } else {
            std::cout << "\t\tProcesso inserido na fila da CPU" << std::endl;
            if (politica) {
                int prioridade = p.getCPU();
                pq.push(prioridade, p);
            } else
                queue.push(p);
        }
    }

    void setBusy(bool b) { busy = b; }

    /**
     * @brief Função que imprime o estado atual da CPU
     *
     */
    void print() {
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

    bool isBusy() { return busy; }

    bool isConcluded() {
        if (!busy && queue.empty() && pq.empty()) return true;
    }

    void setTime() { time++; }

    int getTime() { return time; }

    // Método que executa o processo atual da CPU
    Process* execute() {
        if (busy) {
            if (time == process.getCPU()) {
                std::cout << "\t\tProcesso " << process.getInstant()
                          << " concluido na CPU" << std::endl;
                busy = false;
                return &process;
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
                    std::cout << "\t\tProcesso " << process.getInstant()
                              << " inserido na fila da CPU" << std::endl;
                }
            } else {
                if (!queue.empty()) {
                    process = queue.front();
                    queue.pop();
                    busy = true;
                    time = 0;
                    std::cout << "\t\tProcesso " << process.getInstant()
                              << " inserido na fila da CPU" << std::endl;
                }
            }
        }
        return nullptr;
    }
};

#endif