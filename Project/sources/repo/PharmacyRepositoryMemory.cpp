#include "../../headers/repo/PharmacyRepositoryMemory.h"

std::vector<std::unique_ptr<Produto>>& PharmacyRepositoryMemory::getProdutos() {
    return produtos;
}

std::vector<std::unique_ptr<Funcionario>>& PharmacyRepositoryMemory::getFuncionarios() {
    return funcionarios;
}

std::vector<std::unique_ptr<Receita>>& PharmacyRepositoryMemory::getReceitas() {
    return receitas;
}

std::vector<std::unique_ptr<Venda>>& PharmacyRepositoryMemory::getVendas() {
    return vendas;
}
