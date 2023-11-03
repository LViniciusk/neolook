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

#include <iostream>
#include <vector>

#include "System/System.h"
#include "TAD'S/PriorityQueue.h"
#include "TAD'S/Queue.h"

using namespace std;

int main() {
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
            cout << "Criando sistema com " << qPcs << " pcs e politica "
                 << politica << endl;
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