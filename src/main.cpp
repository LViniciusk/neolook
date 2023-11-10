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

#include "includes/System.h"

using namespace std;

int main() {
    bool politica;
    unsigned short qtdComputadores;
    string arquivo;
    cout << "\n--- NEOLOOK SCALING SIMULATOR ---\n";
    cout << "\n<politica> <Quant. computadores> <arquivo>\n\n";
    cin >> politica >> qtdComputadores >> arquivo;
    cout << endl;
    // Para imprimir o log com mais detalhes, coloque o último parâmetro como true
    System* system = new System(qtdComputadores, politica, false);
    arquivo = "tests/input/" + arquivo;
    // cout << arquivo << endl;
    system->loadFile(arquivo);
    system->execute();
    delete system;
}
