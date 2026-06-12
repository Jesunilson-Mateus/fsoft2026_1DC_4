#include "../../headers/views/RelatorioView.h"
#include "../../headers/exceptions/InvalidDataException.h"
#include "../../headers/views/Utils.h"
#include <iomanip>
#include <iostream>

void RelatorioView::mostrarRelatorio(Controller& controller) {
    RelatorioResumo resumo = controller.gerarRelatorioResumo();
    std::cout << "\nRelatorio resumo\n";
    std::cout << "Produtos registados: " << resumo.totalProdutos << "\n";
    std::cout << "Vendas registadas: " << resumo.totalVendas << "\n";
    std::cout << "Itens vendidos: " << resumo.totalItensVendidos << "\n";
    std::cout << "Total faturado: " << std::fixed << std::setprecision(2)
              << resumo.totalFaturado << " EUR\n";
}

void RelatorioView::gerirRelatorios(Controller& controller) {
    std::cout << "1 - Relatorio resumo\n";
    int opcao{};
    if (!Utils::lerInteiroOpcional("Opcao", opcao)) {
        std::cout << "Operacao cancelada.\n";
        return;
    }

    if (opcao == 1) {
        mostrarRelatorio(controller);
    } else {
        throw InvalidDataException("Opcao invalida");
    }
}
