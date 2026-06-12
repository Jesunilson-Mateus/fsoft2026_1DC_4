#include "../../headers/views/StockView.h"
#include "../../headers/exceptions/InvalidDataException.h"
#include "../../headers/views/ProdutoView.h"
#include "../../headers/views/Utils.h"
#include <iostream>

void StockView::gerirStock(Controller& controller, const std::string& ficheiroStock) {
    std::cout << "1 - Adicionar stock\n";
    std::cout << "2 - Remover stock\n";
    std::cout << "3 - Adicionar produto\n";
    int opcao{};
    if (!Utils::lerInteiroOpcional("Opcao", opcao)) {
        std::cout << "Operacao cancelada.\n";
        return;
    }

    if (opcao == 3) {
        ProdutoView::adicionarProduto(controller);
        controller.guardarStockAtual(ficheiroStock);
        return;
    }

    ProdutoView::listarProdutos(controller);
    int posicaoProduto{};
    int quantidade{};

    if (!Utils::lerInteiroOpcional("\nOpcao do produto", posicaoProduto)) {
        std::cout << "Operacao cancelada.\n";
        return;
    }
    if (!Utils::lerInteiroOpcional("Quantidade", quantidade)) {
        std::cout << "Operacao cancelada.\n";
        return;
    }
    if (quantidade <= 0) {
        throw InvalidDataException("Quantidade deve ser positiva");
    }

    if (opcao == 1) {
        controller.adicionarStock(posicaoProduto, quantidade);
        controller.guardarStockAtual(ficheiroStock);
        std::cout << "Stock adicionado com sucesso.\n";
    } else if (opcao == 2) {
        controller.removerStock(posicaoProduto, quantidade);
        controller.guardarStockAtual(ficheiroStock);
        std::cout << "Stock removido com sucesso.\n";
    } else {
        throw InvalidDataException("Opcao invalida");
    }
}
