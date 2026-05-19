//
// Venda.cpp - Implementação de Venda
//

#include "../../headers/model/Entidades/Venda.h"
#include <stdexcept>

using namespace std;

int Venda::proximoId = 10000;

Venda::Venda()
    : idVenda(++proximoId), dataVenda(), funcionario(nullptr), total(0.0), receita(nullptr) {}

Venda::Venda(const Data& dataVenda, Funcionario* funcionario)
    : idVenda(++proximoId), dataVenda(dataVenda), funcionario(funcionario), total(0.0), receita(nullptr) {
    if (funcionario == nullptr) {
        throw invalid_argument("Funcionário não pode ser nulo.");
    }
}

int Venda::getId() const {
    return idVenda;
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

void Venda::adicionarItem(Produto* produto, int quantidade) {
    if (produto == nullptr) {
        throw invalid_argument("Produto não pode ser nulo.");
    }
    if (quantidade <= 0) {
        throw invalid_argument("Quantidade deve ser maior que zero.");
    }
    if (!produto->verificarDisponibilidade(quantidade)) {
        throw invalid_argument("Stock insuficiente para este produto.");
    }

    ItemVenda item(produto, quantidade, produto->getPreco());
    itens.push_back(item);
}

void Venda::definirReceita(Receita* receita) {
    this->receita = receita;
}

void Venda::calcularTotal() {
    total = 0.0;
    for (const auto& item : itens) {
        total += item.subtotal;
    }
}

double Venda::obterSubtotal() const {
    return total;
}

bool Venda::processarVenda() {
    if (itens.empty()) {
        throw invalid_argument("Venda não pode estar vazia.");
    }

    // Atualizar stock de cada produto
    for (const auto& item : itens) {
        item.produto->atualizarStock(-item.quantidade);
    }

    calcularTotal();
    return true;
}

bool Venda::operator==(const Venda& outra) const {
    return this->idVenda == outra.idVenda;
}

bool Venda::operator==(int id) const {
    return this->idVenda == id;
}

Venda::~Venda() {
    // Não deletar ponteiros, pois são gerenciados pelas classes de gestão
}
