#include "Receita.h"
#include <stdexcept>

bool Receita::ehNomeValido(const std::string& nome) {
    return nome.length() >= 3;
}

Receita::Receita()
        : nomePaciente(""), medicamento(""), codigoReceita(0), medico(""),
          utilizada(false) {}

Receita::Receita(const std::string& nomePaciente, const std::string& medicamento,
                 int codigoReceita, const std::string& medico)
        : utilizada(false) {
    if (!ehNomeValido(nomePaciente)) {
        throw std::invalid_argument("Nome do paciente deve ter pelo menos 3 caracteres.");
    }
    if (medicamento.empty()) {
        throw std::invalid_argument("Medicamento nao pode estar vazio.");
    }
    if (medico.empty()) {
        throw std::invalid_argument("Medico nao pode estar vazio.");
    }
    if (codigoReceita < 10000 || codigoReceita > 99999) {
        throw std::invalid_argument("Codigo da receita deve ter 5 digitos.");
    }

    this->nomePaciente = nomePaciente;
    this->medicamento = medicamento;
    this->codigoReceita = codigoReceita;
    this->medico = medico;
}

const std::string& Receita::getNomePaciente() const {
    return nomePaciente;
}

const std::string& Receita::getMedicamento() const {
    return medicamento;
}

int Receita::getCodigoReceita() const {
    return codigoReceita;
}

const std::string& Receita::getMedico() const {
    return medico;
}

bool Receita::foiUtilizada() const {
    return utilizada;
}

bool Receita::ehValida() const {
    return !utilizada;
}

bool Receita::validarCodigo(int codigo) const {
    if (!ehValida() || codigo != codigoReceita) {
        throw std::invalid_argument("Receita invalida, utilizada ou codigo incorreto.");
    }
    return true;
}

void Receita::marcarComoUtilizada() {
    utilizada = true;
}

bool Receita::operator==(const Receita& outra) const {
    return codigoReceita == outra.codigoReceita;
}
