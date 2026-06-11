#include "Medicamento.h"

Medicamento::Medicamento()
    : Produto(), requerReceita(false) {}

Medicamento::Medicamento(const std::string& nome, const std::string& categoria,
                         double preco, int quantidadeStock, bool requerReceita,
                         const std::string& descricao)
    : Produto(nome, categoria, preco, quantidadeStock, descricao),
      requerReceita(requerReceita) {}

bool Medicamento::getRequerReceita() const {
    return requerReceita;
}

void Medicamento::setRequerReceita(bool requerReceita) {
    this->requerReceita = requerReceita;
}
