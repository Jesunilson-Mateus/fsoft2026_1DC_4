#include "../../headers/repo/RepositorioFarmaciaMemoria.h"
#include <fstream>
#include <stdexcept>

RepositorioFarmaciaMemoria::RepositorioFarmaciaMemoria(const std::string& nomeFarmacia)
        : farmacia(nomeFarmacia) {}

Farmacia& RepositorioFarmaciaMemoria::getFarmacia() {
    return farmacia;
}

const Farmacia& RepositorioFarmaciaMemoria::getFarmacia() const {
    return farmacia;
}

std::vector<std::unique_ptr<Cliente>>& RepositorioFarmaciaMemoria::getClientes() {
    return farmacia.getClientes();
}

std::vector<std::unique_ptr<Produto>>& RepositorioFarmaciaMemoria::getProdutos() {
    return farmacia.getProdutos();
}

std::vector<std::unique_ptr<Funcionario>>& RepositorioFarmaciaMemoria::getFuncionarios() {
    return farmacia.getFuncionarios();
}

std::vector<std::unique_ptr<Receita>>& RepositorioFarmaciaMemoria::getReceitas() {
    return farmacia.getReceitas();
}

std::vector<std::unique_ptr<Venda>>& RepositorioFarmaciaMemoria::getVendas() {
    return farmacia.getVendas();
}

Funcionario& RepositorioFarmaciaMemoria::guardarFuncionario(
        std::unique_ptr<Funcionario> funcionario) {
    return farmacia.guardarFuncionario(std::move(funcionario));
}

void RepositorioFarmaciaMemoria::removerFuncionarioPorPosicao(int posicaoFuncionario) {
    farmacia.removerFuncionarioPorPosicao(posicaoFuncionario);
}

void RepositorioFarmaciaMemoria::carregarStockGuardado(const std::string& caminhoFicheiro) {
    std::ifstream ficheiro(caminhoFicheiro);
    if (!ficheiro) {
        return;
    }

    int posicao{};
    int quantidadeGuardada{};
    auto& produtos = farmacia.getProdutos();
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
    const auto& produtos = farmacia.getProdutos();
    for (const auto& produto : produtos) {
        ficheiro << posicao++ << " " << produto->getQuantidadeStock() << "\n";
    }
}
