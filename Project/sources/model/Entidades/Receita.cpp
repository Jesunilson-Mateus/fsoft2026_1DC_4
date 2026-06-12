#include "Receita.h"
#include <stdexcept>

bool Receita::ehNomeValido(const std::string& nome) {
    return nome.length() >= 3;
}

Receita::Receita()
        : cliente(nullptr), medicamento(""), codigoReceita(0), medico(""),
          utilizada(false) {}

Receita::Receita(Cliente* cliente, const std::string& medicamento,
                 int codigoReceita, const std::string& medico)
        : cliente(cliente), utilizada(false) {
    if (cliente == nullptr || !ehNomeValido(cliente->getNome())) {
        throw std::invalid_argument("Cliente da receita deve ser valido.");
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

    this->medicamento = medicamento;
    this->codigoReceita = codigoReceita;
    this->medico = medico;
}

Cliente* Receita::getCliente() const {
    return cliente;
}

const std::string& Receita::getNomePaciente() const {
    static const std::string vazio = "";
    return cliente != nullptr ? cliente->getNome() : vazio;
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
