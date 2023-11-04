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

int main() {
    std::cout << "\033[2J\033[1;1H";

    // Título estilizado para o projeto Neolook
    std::cout << "=========================================" << std::endl;
    std::cout << "            NEOLOOK SIMULATOR           " << std::endl;
    std::cout << "=========================================" << std::endl;

    std::cout << std::endl;
    std::cout << "Comandos:" << std::endl;
    std::cout
        << "init <qtd pcs> <politica> - Cria o sistema com a quantidade de pcs "
           "e a politica de escalonamento"
        << std::endl;
    std::cout << "load <arq> - Carrega o arquivo trace" << std::endl;
    std::cout << "print - Imprime o estado atual do sistema" << std::endl;
    std::cout << "execute - Executa o sistema" << std::endl;
    std::cout << "exit - Sai do programa" << std::endl;
    std::cout << std::endl;

    int qPcs;
    string arq;
    bool politica;
    System* sys;

    // comandos:
    // init <qtd pcs> <politica> - Cria o sistema com a quantidade de pcs e a
    // politica de escalonamento load <arq> - Carrega o arquivo trace

    while (true) {
        string cmd;
        cin >> cmd;
        if (cmd == "init") {
            cin >> qPcs >> politica;
            sys = new System(qPcs, politica);
        } else if (cmd == "load") {
            cin >> arq;
            sys->loadFile(arq);
        } else if (cmd == "print") {
            sys->print();
        } else if (cmd == "execute") {
            sys->execute();
        } else if (cmd == "exit") {
            break;
        } else {
            cout << "Comando inválido" << endl;
        }
    }

    return 0;
}