#include "Produto.h"
#include <stdexcept>

bool Produto::ehNomeValido(const std::string& nome) {
    return nome.length() >= 3;
}

bool Produto::ehPrecoValido(double preco) {
    return preco > 0.0;
}

bool Produto::ehQuantidadeValida(int quantidade) {
    return quantidade >= 0;
}

Produto::Produto()
        : nome(""), categoria(""), preco(0.0), quantidadeStock(0), descricao("") {}

Produto::Produto(const std::string& nome, const std::string& categoria,
                 double preco, int quantidadeStock, const std::string& descricao)
{
    if (!ehNomeValido(nome)) {
        throw std::invalid_argument("Nome do produto deve ter pelo menos 3 caracteres.");
    }
    if (!ehPrecoValido(preco)) {
        throw std::invalid_argument("Preco deve ser maior que zero.");
    }
    if (!ehQuantidadeValida(quantidadeStock)) {
        throw std::invalid_argument("Quantidade nao pode ser negativa.");
    }

    this->nome = nome;
    this->categoria = categoria;
    this->preco = preco;
    this->quantidadeStock = quantidadeStock;
    this->descricao = descricao;
}

const std::string& Produto::getNome() const {
    return nome;
}

const std::string& Produto::getCategoria() const {
    return categoria;
}

double Produto::getPreco() const {
    return preco;
}

int Produto::getQuantidadeStock() const {
    return quantidadeStock;
}

const std::string& Produto::getDescricao() const {
    return descricao;
}

void Produto::setNome(const std::string& nome) {
    if (!ehNomeValido(nome)) {
        throw std::invalid_argument("Nome invalido.");
    }
    this->nome = nome;
}

void Produto::setCategoria(const std::string& categoria) {
    this->categoria = categoria;
}

void Produto::setPreco(double preco) {
    if (!ehPrecoValido(preco)) {
        throw std::invalid_argument("Preco invalido.");
    }
    this->preco = preco;
}

void Produto::setDescricao(const std::string& descricao) {
    this->descricao = descricao;
}

bool Produto::verificarDisponibilidade(int quantidade) const {
    return quantidade > 0 && quantidadeStock >= quantidade;
}

void Produto::atualizarStock(int quantidade) {
    int novaQuantidade = quantidadeStock + quantidade;
    if (novaQuantidade < 0) {
        throw std::invalid_argument("Quantidade em stock nao pode ser negativa.");
    }
    quantidadeStock = novaQuantidade;
}

void Produto::adicionarStock(int quantidade) {
    if (quantidade <= 0) {
        throw std::invalid_argument("Quantidade a adicionar deve ser positiva.");
    }
    quantidadeStock += quantidade;
}

void Produto::removerStock(int quantidade) {
    if (quantidade <= 0) {
        throw std::invalid_argument("Quantidade a remover deve ser positiva.");
    }
    if (quantidadeStock < quantidade) {
        throw std::invalid_argument("Stock insuficiente para remover.");
    }
    quantidadeStock -= quantidade;
}

bool Produto::operator==(const Produto& outro) const {
    return nome == outro.nome && categoria == outro.categoria;
}
