#include "Receita.h"
#include <stdexcept>

int Receita::proximoId = 5000;

bool Receita::ehNomeValido(const std::string& nome) {
    return nome.length() >= 3;
}

Receita::Receita()
    : id(++proximoId), nomePaciente(""), medicamento(""), dataValidade(), medico(""),
      utilizada(false) {}

Receita::Receita(const std::string& nomePaciente, const std::string& medicamento,
                 const Data& dataValidade, const std::string& medico)
    : id(++proximoId), utilizada(false) {
    if (!ehNomeValido(nomePaciente)) {
        throw std::invalid_argument("Nome do paciente deve ter pelo menos 3 caracteres.");
    }
    if (medicamento.empty()) {
        throw std::invalid_argument("Medicamento nao pode estar vazio.");
    }
    if (medico.empty()) {
        throw std::invalid_argument("Medico nao pode estar vazio.");
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
    return !utilizada && Data(19, 5, 2026) < dataValidade;
}

bool Receita::validar() {
    if (!ehValida()) {
        throw std::invalid_argument("Receita invalida ou expirada.");
    }
    return true;
}

void Receita::marcarComoUtilizada() {
    utilizada = true;
}

bool Receita::operator==(const Receita& outra) const {
    return id == outra.id;
}

bool Receita::operator==(int id) const {
    return this->id == id;
}
