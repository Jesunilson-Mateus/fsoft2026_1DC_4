#include "Medicamento.h"

Medicamento::Medicamento()
    : Produto(), requerReceita(false), dosagem(""), fabricante(""), dataValidade() {}

Medicamento::Medicamento(const std::string& nome, const std::string& categoria,
                         double preco, int quantidadeStock, bool requerReceita,
                         const std::string& dosagem, const std::string& fabricante,
                         const Data& dataValidade, const std::string& descricao)
    : Produto(nome, categoria, preco, quantidadeStock, descricao),
      requerReceita(requerReceita), dosagem(dosagem), fabricante(fabricante),
      dataValidade(dataValidade) {}

bool Medicamento::getRequerReceita() const {
    return requerReceita;
}

const std::string& Medicamento::getDosagem() const {
    return dosagem;
}

const std::string& Medicamento::getFabricante() const {
    return fabricante;
}

const Data& Medicamento::getDataValidade() const {
    return dataValidade;
}

void Medicamento::setRequerReceita(bool requerReceita) {
    this->requerReceita = requerReceita;
}

void Medicamento::setDosagem(const std::string& dosagem) {
    this->dosagem = dosagem;
}

void Medicamento::setFabricante(const std::string& fabricante) {
    this->fabricante = fabricante;
}

void Medicamento::setDataValidade(const Data& dataValidade) {
    this->dataValidade = dataValidade;
}

bool Medicamento::ehValido() const {
    return Data(19, 5, 2026) < dataValidade;
}
