#include "Project/Mock/MockData.h"
#include "Project/headers/controllers/Controller.h"
#include "Project/headers/repo/RepositorioFarmaciaMemoria.h"
#include "Project/headers/views/Views.h"
#include <exception>
#include <iostream>
#include <string>

const std::string FICHEIRO_STOCK = "stock_persistente.txt";

int main() {
    try {
        RepositorioFarmaciaMemoria repositorio;
        Controller controller(&repositorio);

        MockData::carregarDadosIniciais(controller);
        controller.carregarStockGuardado(FICHEIRO_STOCK);

        Views::executar(controller, FICHEIRO_STOCK);
        return 0;
    } catch (const std::exception& erro) {
        std::cout << "Erro critico ao iniciar programa: " << erro.what() << "\n";
        return 1;
    }
}
