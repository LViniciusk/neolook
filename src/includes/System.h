/**
 * @file System.h
 * @author Júnior Silva (junior.silva@alu.ufc.br) - 554222
 * @author Linyker Vinicius (botlink2030@alu.ufc.br) - 556280
 * @brief Classe que representa o sistema.
 * @version 0.1
 * @date 06-11-2023
 *
 *
 */

#ifndef SYSTEM_H
#define SYSTEM_H

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "../tads/Vector.h"
#include "Computer.h"
#include "LogFile.h"
#include "Process.h"
#include "Resource.h"

extern const std::string inputPath;

/**
 * @brief Classe que representa o sistema como um todo.
 * Possui um vetor de computadores, uma rede e um vetor de processos.
 * Possui também um vetor de eventos, que é utilizado para gerar o log do sistema.
 * Possui um relógio lógico, que é incrementado a cada iteração do loop principal.
 * Possui também o tempo médio de espera, o tempo médio de execução e a taxa de processamento do sistema.
 *
 */
class System {
   private:
    unsigned short qPcs;           // quantidade de computadores
    Vector<Computer*> computers;   // computadores do sistema
    Network* network;              // rede do sistema
    bool politica;                 // politica de escalonamento
    Vector<Process>* processos{};  // vetor de processos
    unsigned timer{};              // relógio lógico do sistema
    double tempoMedioEspera{};     // tempo médio de espera do sistema
    double tempoMedioExecucao{};   // tempo médio de execução do sistema
    double taxaProcessamento{};    // taxa de processamento do sistema
    bool printLog{};               // flag para imprimir o log do sistema
    unsigned qtdProcessos{};       // quantidade de processos
    LogFile* logFile;              // arquivo de log do sistema

   public:
    /**
     * @brief Construtor parametrizado da classe System.
     * Cria um vetor de computadores, uma rede e um vetor de processos.
     * O timer é inicializado com -1, pois o primeiro processo chega no instante 0.
     *
     * @param qPcs Quantidade de computadores
     * @param arq Arquivo trace a ser carregado
     * @param politica Política de escalonamento. 0 - FCFS, 1 - SJF
     */
    System(unsigned short qPcs, bool pol, bool printLog);

    /**
     * @brief Destrutor da classe System.
     * Libera a memória alocada para os computadores, a rede, o vetor de processos e o vetor de eventos.
     *
     */
    ~System();

    /**
     * @brief Função que carrega o arquivo trace para o vetor de processos.
     *
     * @param arq Arquivo trace a ser carregado
     */
    void loadFile(std::string arq);

    /**
     * @brief Função que executa o sistema.
     * O sistema é executado enquanto houverem processos pendentes.
     * A cada iteração do loop principal:
     * -    O timer é incrementado
     * -    Os processos que chegam no instante atual são enviados para a CPU
     * -    Para cada computador:
     *     -   Se a CPU estiver ociosa, o processo é carregado da fila de processos
     *     -   Se a CPU estiver ocupada, o processo é executado
     *     -   Se o processo terminar na CPU, ele é enviado para um disco aleatório
     * -    Para cada disco:
     *     -   Se o disco estiver ocioso, o processo é carregado da fila de processos
     *     -   Se o disco estiver ocupado, o processo é executado
     *     -    Se o processo terminar no disco, ele é enviado para a rede
     * -    Para a rede:
     *     -    Se a rede estiver ociosa, o processo é carregado da fila de processos
     *     -    Se a rede estiver ocupada, o processo é executado
     *     -    Se o processo terminar na rede, ele é removido do sistema
     * -    O loop principal é encerrado quando não houverem mais processos pendentes
     *
     * Após a execução do sistema, são calculados o tempo médio de espera,
     * o tempo médio de execução e a taxa de processamento.
     * Por fim, o log do sistema é impresso no arquivo log.txt.
     *
     */
    void execute();
};

#endif  // SYSTEM_H
