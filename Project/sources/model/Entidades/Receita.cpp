//
// Receita.cpp - Implementação de Receita
//

#include "../../headers/model/Entidades/Receita.h"
#include <stdexcept>

using namespace std;

int Receita::proximoId = 5000;

bool Receita::ehNomeValido(const std::string& nome) {
    return nome.length() >= 3;
}

Receita::Receita()
    : id(++proximoId), nomePaciente(""), medicamento(""), dataValidade(), medico(""), utilizada(false) {}

Receita::Receita(const std::string& nomePaciente, const std::string& medicamento,
                  const Data& dataValidade, const std::string& medico)
    : id(++proximoId), utilizada(false) {
    if (!ehNomeValido(nomePaciente)) {
        throw invalid_argument("Nome do paciente deve ter pelo menos 3 caracteres.");
    }
    if (medicamento.empty()) {
        throw invalid_argument("Medicamento não pode estar vazio.");
    }
    if (medico.empty()) {
        throw invalid_argument("Médico não pode estar vazio.");
    }

    this->nomePaciente = nomePaciente;
    this->medicamento = medicamento;
    this->dataValidade = dataValidade;
    this->medico = medico;
}

int Receita::getId() const {
    return id;
}

const std::string& Receita::getNomePaciente() const {
    return nomePaciente;
}

const std::string& Receita::getMedicamento() const {
    return medicamento;
}

const Data& Receita::getDataValidade() const {
    return dataValidade;
}

const std::string& Receita::getMedico() const {
    return medico;
}

bool Receita::foiUtilizada() const {
    return utilizada;
}

bool Receita::ehValida() const {
    if (utilizada) {
        return false;
    }
    // Verificar se a receita ainda não expirou
    Data dataAtual(19, 5, 2026); // Data atual do sistema (exemplo)
    return dataAtual < dataValidade;
}

bool Receita::validar() {
    if (!ehValida()) {
        throw invalid_argument("Receita inválida ou expirada.");
    }
    return true;
}

void Receita::marcarComoUtilizada() {
    this->utilizada = true;
}

bool Receita::operator==(const Receita& outra) const {
    return this->id == outra.id;
}

bool Receita::operator==(int id) const {
    return this->id == id;
}
