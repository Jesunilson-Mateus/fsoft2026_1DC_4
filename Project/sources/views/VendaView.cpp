#include "../../headers/views/VendaView.h"
#include "../../headers/exceptions/DataConsistencyException.h"
#include "../../headers/exceptions/InvalidDataException.h"
#include "../../headers/exceptions/NoDataException.h"
#include "../../headers/model/Entidades/Medicamento.h"
#include "../../headers/views/ProdutoView.h"
#include "../../headers/views/Utils.h"
#include <cctype>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

void VendaView::registarVenda(Controller& controller, const std::string& ficheiroStock) {
    ProdutoView::listarProdutos(controller);

    std::vector<std::pair<int, int>> itens;
    std::map<int, int> quantidadesPorProduto;
    bool precisaReceita = false;
    bool receitaValidada = false;
    std::string nomeCliente;
    std::string nifCliente;

    if (!Utils::lerTextoOpcional("Nome do cliente", nomeCliente)) {
        std::cout << "Venda cancelada.\n";
        return;
    }
    if (nomeCliente.empty() || nomeCliente.length() < 3) {
        throw InvalidDataException("Nome do cliente deve ter pelo menos 3 caracteres");
    }

    if (!Utils::lerTextoOpcional("NIF do cliente", nifCliente)) {
        std::cout << "Venda cancelada.\n";
        return;
    }
    if (!nifCliente.empty() && nifCliente.length() != 9) {
        throw InvalidDataException("NIF do cliente deve ter 9 digitos");
    }
    for (char digito : nifCliente) {
        if (!std::isdigit(static_cast<unsigned char>(digito))) {
            throw InvalidDataException("NIF do cliente deve conter apenas digitos");
        }
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

    Venda& venda = controller.registarVenda(itens, Data(19, 5, 2026), nomeCliente, nifCliente,
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
