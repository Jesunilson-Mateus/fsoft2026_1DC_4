#include "../../headers/repo/RepositorioFarmaciaMemoria.h"
#include <fstream>
#include <stdexcept>

std::vector<std::unique_ptr<Cliente>>& RepositorioFarmaciaMemoria::getClientes() {
    return clientes;
}

std::vector<std::unique_ptr<Produto>>& RepositorioFarmaciaMemoria::getProdutos() {
    return produtos;
}

std::vector<std::unique_ptr<Funcionario>>& RepositorioFarmaciaMemoria::getFuncionarios() {
    return funcionarios;
}

std::vector<std::unique_ptr<Receita>>& RepositorioFarmaciaMemoria::getReceitas() {
    return receitas;
}

std::vector<std::unique_ptr<Venda>>& RepositorioFarmaciaMemoria::getVendas() {
    return vendas;
}

Funcionario& RepositorioFarmaciaMemoria::guardarFuncionario(
        std::unique_ptr<Funcionario> funcionario) {
    if (funcionario == nullptr) {
        throw std::invalid_argument("Funcionario nao pode ser nulo.");
    }
    funcionarios.push_back(std::move(funcionario));
    return *funcionarios.back();
}

void RepositorioFarmaciaMemoria::removerFuncionarioPorPosicao(int posicaoFuncionario) {
    if (posicaoFuncionario < 1 || posicaoFuncionario > static_cast<int>(funcionarios.size())) {
        throw std::invalid_argument("Funcionario nao encontrado.");
    }
    funcionarios.erase(funcionarios.begin() + (posicaoFuncionario - 1));
}

void RepositorioFarmaciaMemoria::carregarStockGuardado(const std::string& caminhoFicheiro) {
    std::ifstream ficheiro(caminhoFicheiro);
    if (!ficheiro) {
        return;
    }

    int posicao{};
    int quantidadeGuardada{};
    while (ficheiro >> posicao >> quantidadeGuardada) {
        if (posicao >= 1 && posicao <= static_cast<int>(produtos.size()) && quantidadeGuardada >= 0) {
            Produto* produto = produtos[posicao - 1].get();
            produto->atualizarStock(quantidadeGuardada - produto->getQuantidadeStock());
        }
    }
}

void RepositorioFarmaciaMemoria::guardarStock(const std::string& caminhoFicheiro) const {
    std::ofstream ficheiro(caminhoFicheiro);
    if (!ficheiro) {
        return;
    }

    int posicao = 1;
    for (const auto& produto : produtos) {
        ficheiro << posicao++ << " " << produto->getQuantidadeStock() << "\n";
    }
}
