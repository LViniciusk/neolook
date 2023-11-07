/**
 * @file main.cpp
 * @author Júnior Silva (junior.silva@alu.ufc.br) - 554222
 * @author Linyker Vinicius (botlink2030@alu.ufc.br) - 556280
 * @brief
 * @version 0.1
 * @date 20-10-2023
 *
 *
 */

#include <iomanip>
#include <iostream>
#include <vector>

#include "System/System.h"
#include "TAD'S/PriorityQueue.h"
#include "TAD'S/Queue.h"

using namespace std;

// PARA COMPILAR:
//     make all

// PARA EXECUTAR:
//     ./main <politica> <arquivo> <Quant. computadores>

// A política de escalonamento pode ser:
// 0 - FCFS (First Come, First Served)
// 1 - SJF (Shortest Job First)

// Um quinto argumento opcional pode ser passado para ativar o log detalhado.
// 0 - Log detalhado desativado
// 1 - Log detalhado ativado

// A saída do programa será impressa no terminal.
// A saída do programa será gerada na pasta "out".

int main(int argc, char* argv[]) {
    // verifica se a quantidade de argumentos é válida
    if (argc < 4 || argc > 5) {
        cout << "Quantidade de argumentos inválida" << endl;
        cout << "Uso: ./main <politica> <arquivo> <Quant. computadores> " << endl;
        return 1;
    }

    // verifica se a politica de escalonamento é válida
    if (atoi(argv[1]) != 0 && atoi(argv[1]) != 1) {
        cout << "Politica de escalonamento inválida" << endl;
        cout << "0 - FCFS" << endl;
        cout << "1 - SJF" << endl;
        return 1;
    }

    // verifica se a quantidade de computadores é válida
    if (atoi(argv[3]) <= 0) {
        cout << "Quantidade de computadores inválida" << endl;
        return 1;
    }

    int politica = atoi(argv[1]);
    int qtdComputadores = atoi(argv[3]);
    std::string arquivo = "testes/";
    arquivo += argv[2];
    bool logFileDetalhado = atoi(argv[4]);

    // cria o sistema
    System* system = new System(qtdComputadores, politica, logFileDetalhado);

    // carrega os processos do arquivo
    system->loadFile(arquivo);

    // executa o sistema
    system->execute();

    // deleta o sistema
    delete system;

    return 0;
}
