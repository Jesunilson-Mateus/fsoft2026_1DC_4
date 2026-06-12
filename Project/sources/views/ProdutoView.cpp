#include "../../headers/views/ProdutoView.h"
#include "../../headers/exceptions/InvalidDataException.h"
#include "../../headers/model/Entidades/Medicamento.h"
#include "../../headers/views/Utils.h"
#include <iomanip>
#include <iostream>

void ProdutoView::listarProdutos(const Controller& controller) {
    std::cout << "\nProdutos em stock\n";
    std::cout << std::left << std::setw(8) << "Opcao" << std::setw(22) << "Nome"
              << std::setw(16) << "Categoria" << std::setw(10) << "Preco"
              << std::setw(8) << "Stock" << "Receita\n";

    int opcao = 1;
    for (const auto& produto : controller.listarProdutos()) {
        Medicamento* medicamento = dynamic_cast<Medicamento*>(produto.get());
        std::cout << std::left << std::setw(8) << opcao++
                  << std::setw(22) << produto->getNome()
                  << std::setw(16) << produto->getCategoria()
                  << std::setw(10) << std::fixed << std::setprecision(2) << produto->getPreco()
                  << std::setw(8) << produto->getQuantidadeStock()
                  << (medicamento != nullptr && medicamento->getRequerReceita() ? "Sim" : "Nao")
                  << "\n";
    }
}

void ProdutoView::adicionarProduto(Controller& controller) {
    std::string nome;
    double preco{};
    int stock{};

    if (!Utils::lerTextoOpcional("Nome", nome)) {
        std::cout << "Adicao cancelada.\n";
        return;
    }
    if (nome.empty() || nome.length() < 2) {
        throw InvalidDataException("Nome do produto deve ter pelo menos 2 caracteres");
    }

    if (!Utils::lerDoubleOpcional("Preco", preco)) {
        std::cout << "Adicao cancelada.\n";
        return;
    }
    if (preco <= 0) {
        throw InvalidDataException("Preco deve ser positivo");
    }

    if (!Utils::lerInteiroOpcional("Stock inicial", stock)) {
        std::cout << "Adicao cancelada.\n";
        return;
    }
    if (stock < 0) {
        throw InvalidDataException("Stock nao pode ser negativo");
    }

    std::cout << "1 - Produto comum\n";
    std::cout << "2 - Medicamento\n";
    int tipo{};
    if (!Utils::lerInteiroOpcional("Tipo", tipo)) {
        std::cout << "Adicao cancelada.\n";
        return;
    }

    if (tipo == 1) {
        controller.adicionarProduto(nome, "Produto comum", preco, stock);
    } else if (tipo == 2) {
        int requerReceita{};
        if (!Utils::lerInteiroOpcional("Requer receita? (1 sim, 0 nao)", requerReceita)) {
            std::cout << "Adicao cancelada.\n";
            return;
        }
        controller.adicionarMedicamento(nome, "Medicamento", preco, stock, requerReceita == 1);
    } else {
        throw InvalidDataException("Tipo de produto invalido");
    }

    std::cout << "Produto adicionado com sucesso.\n";
}
