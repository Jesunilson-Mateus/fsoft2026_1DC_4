#include "Farmacia.h"
#include <stdexcept>

Farmacia::Farmacia(const std::string& nome) : nome(nome) {
    if (nome.empty()) {
        throw std::invalid_argument("Nome da farmacia nao pode estar vazio.");
    }
}

const std::string& Farmacia::getNome() const {
    return nome;
}

void Farmacia::setNome(const std::string& nome) {
    if (nome.empty()) {
        throw std::invalid_argument("Nome da farmacia nao pode estar vazio.");
    }
    this->nome = nome;
}

std::vector<std::unique_ptr<Cliente>>& Farmacia::getClientes() {
    return clientes;
}

std::vector<std::unique_ptr<Produto>>& Farmacia::getProdutos() {
    return produtos;
}

std::vector<std::unique_ptr<Funcionario>>& Farmacia::getFuncionarios() {
    return funcionarios;
}

std::vector<std::unique_ptr<Receita>>& Farmacia::getReceitas() {
    return receitas;
}

std::vector<std::unique_ptr<Venda>>& Farmacia::getVendas() {
    return vendas;
}

const std::vector<std::unique_ptr<Produto>>& Farmacia::getProdutos() const {
    return produtos;
}

Funcionario& Farmacia::guardarFuncionario(std::unique_ptr<Funcionario> funcionario) {
    if (funcionario == nullptr) {
        throw std::invalid_argument("Funcionario nao pode ser nulo.");
    }
    funcionarios.push_back(std::move(funcionario));
    return *funcionarios.back();
}

void Farmacia::removerFuncionarioPorPosicao(int posicaoFuncionario) {
    if (posicaoFuncionario < 1 || posicaoFuncionario > static_cast<int>(funcionarios.size())) {
        throw std::invalid_argument("Funcionario nao encontrado.");
    }
    funcionarios.erase(funcionarios.begin() + (posicaoFuncionario - 1));
}
