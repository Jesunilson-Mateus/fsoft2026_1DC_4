#include "../../headers/views/ClienteView.h"
#include <iomanip>
#include <iostream>

void ClienteView::listarClientes(const Controller& controller) {
    std::cout << "\nClientes registados\n";
    std::cout << std::left << std::setw(8) << "Opcao" << std::setw(24) << "Nome"
              << std::setw(16) << "NIF" << "Telefone\n";

    int opcao = 1;
    for (const auto& cliente : controller.listarClientes()) {
        std::cout << std::left << std::setw(8) << opcao++
                  << std::setw(24) << cliente->getNome()
                  << std::setw(16) << cliente->getNif()
                  << cliente->getTelefone()
                  << "\n";
    }
}
