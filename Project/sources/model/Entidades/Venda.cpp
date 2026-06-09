#include "Venda.h"
#include <stdexcept>

ItemVenda::ItemVenda(Produto* produto, int quantidade, double precoUnitario)
        : produto(produto), quantidade(quantidade), precoUnitario(precoUnitario),
          subtotal(quantidade * precoUnitario) {}

Venda::Venda() : dataVenda(), funcionario(nullptr), total(0.0), receita(nullptr) {}

Venda::Venda(const Data& dataVenda, Funcionario* funcionario)
        : dataVenda(dataVenda), funcionario(funcionario), total(0.0), receita(nullptr) {
    if (funcionario == nullptr) {
        throw std::invalid_argument("Funcionario nao pode ser nulo.");
    }
}

const Data& Venda::getDataVenda() const {
    return dataVenda;
}

Funcionario* Venda::getFuncionario() const {
    return funcionario;
}

const std::vector<ItemVenda>& Venda::getItens() const {
    return itens;
}

double Venda::getTotal() const {
    return total;
}

Receita* Venda::getReceita() const {
    return receita;
}

const std::string& Venda::getNomePaciente() const {
    return nomePaciente;
}

void Venda::adicionarItem(Produto* produto, int quantidade) {
    if (produto == nullptr) {
        throw std::invalid_argument("Produto nao pode ser nulo.");
    }
    if (!produto->verificarDisponibilidade(quantidade)) {
        throw std::invalid_argument("Stock insuficiente para este produto.");
    }

    itens.push_back(ItemVenda(produto, quantidade, produto->getPreco()));
}

void Venda::definirReceita(Receita* receita) {
    this->receita = receita;
}

void Venda::definirNomePaciente(const std::string& nomePaciente) {
    this->nomePaciente = nomePaciente;
}

void Venda::calcularTotal() {
    total = 0.0;
    for (const auto& item : itens) {
        total += item.subtotal;
    }
}

bool Venda::processarVenda() {
    if (itens.empty()) {
        throw std::invalid_argument("Venda nao pode estar vazia.");
    }

    for (const auto& item : itens) {
        item.produto->atualizarStock(-item.quantidade);
    }

    calcularTotal();
    return true;
}

bool Venda::operator==(const Venda& outra) const {
    return funcionario == outra.funcionario && dataVenda == outra.dataVenda && total == outra.total;
}
