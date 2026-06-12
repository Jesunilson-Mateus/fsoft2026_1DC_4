#include "../../headers/views/VendaView.h"
#include "../../headers/exceptions/DataConsistencyException.h"
#include "../../headers/exceptions/InvalidDataException.h"
#include "../../headers/exceptions/NoDataException.h"
#include "../../headers/model/Entidades/Medicamento.h"
#include "../../headers/views/ProdutoView.h"
#include "../../headers/views/Utils.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

void VendaView::listarReceitas(const Controller& controller) {
    std::cout << "\nReceitas disponiveis\n";
    std::cout << std::left << std::setw(22) << "Paciente" << std::setw(22)
              << "Medicamento" << std::setw(18) << "Codigo da receita" << "Estado\n";

    for (const auto& receita : controller.listarReceitas()) {
        std::cout << std::left << std::setw(22) << receita->getNomePaciente()
                  << std::setw(22) << receita->getMedicamento()
                  << std::setw(18) << receita->getCodigoReceita()
                  << (receita->foiUtilizada() ? "Utilizada" : "Disponivel")
                  << "\n";
    }
}

void VendaView::registarVenda(Controller& controller, const std::string& ficheiroStock) {
    ProdutoView::listarProdutos(controller);

    std::vector<std::pair<int, int>> itens;
    std::map<int, int> quantidadesPorProduto;
    bool precisaReceita = false;
    bool receitaValidada = false;
    std::string nomeCliente;

    if (!Utils::lerTextoOpcional("Nome do cliente", nomeCliente)) {
        std::cout << "Venda cancelada.\n";
        return;
    }

    while (true) {
        int posicaoProduto{};
        if (!Utils::lerInteiroOpcional("\nOpcao do produto (0 para terminar venda)", posicaoProduto)) {
            std::cout << "Venda cancelada.\n";
            return;
        }
        if (posicaoProduto == 0) break;

        int quantidade{};
        if (!Utils::lerInteiroOpcional("Quantidade", quantidade)) {
            std::cout << "Venda cancelada.\n";
            return;
        }
        if (quantidade <= 0) {
            throw InvalidDataException("Quantidade deve ser positiva");
        }

        Produto* produto = controller.obterProdutoPorPosicao(posicaoProduto);
        if (produto == nullptr) {
            throw NoDataException("Produto nao encontrado");
        }

        int quantidadeTotal = quantidadesPorProduto[posicaoProduto] + quantidade;
        if (quantidadeTotal > produto->getQuantidadeStock()) {
            throw DataConsistencyException("Stock insuficiente para esta quantidade");
        }

        Medicamento* medicamento = dynamic_cast<Medicamento*>(produto);
        if (medicamento != nullptr && medicamento->getRequerReceita()) {
            precisaReceita = true;
            std::cout << "Este medicamento requer receita.\n";
            if (!Utils::lerSimNao("A receita e valida?")) {
                throw InvalidDataException("Medicamento requer receita valida");
            }
            receitaValidada = true;
        }

        itens.push_back({posicaoProduto, quantidade});
        quantidadesPorProduto[posicaoProduto] = quantidadeTotal;
    }

    if (itens.empty()) {
        throw InvalidDataException("Nenhum item foi selecionado para a venda");
    }

    Venda& venda = controller.registarVenda(itens, Data(19, 5, 2026), nomeCliente,
                                            receitaValidada);
    controller.guardarStockAtual(ficheiroStock);

    std::cout << "Venda registada com sucesso em nome de " << venda.getNomePaciente();
    if (precisaReceita) {
        std::cout << ". Receita registada";
        if (venda.getReceita() != nullptr) {
            std::cout << " para " << venda.getReceita()->getMedicamento();
        }
    }
    std::cout << ". Total: " << std::fixed << std::setprecision(2)
              << venda.getTotal() << " EUR\n";
}
