#include "Cliente.h"
#include <cctype>
#include <stdexcept>

Cliente::Cliente() : nome(""), nif(""), telefone("") {}

bool Cliente::ehNomeValido(const std::string& nome) {
    return nome.length() >= 3;
}

bool Cliente::ehNifValido(const std::string& nif) {
    if (nif.empty()) {
        return true;
    }
    if (nif.length() != 9) {
        return false;
    }
    for (char digito : nif) {
        if (!std::isdigit(static_cast<unsigned char>(digito))) {
            return false;
        }
    }
    return true;
}

Cliente::Cliente(const std::string& nome,
                 const std::string& nif,
                 const std::string& telefone)
        : nome(nome), nif(nif), telefone(telefone) {
    if (!ehNomeValido(nome)) {
        throw std::invalid_argument("Nome do cliente deve ter pelo menos 3 caracteres.");
    }
    if (!ehNifValido(nif)) {
        throw std::invalid_argument("NIF do cliente deve ter 9 digitos.");
    }
}

const std::string& Cliente::getNome() const {
    return nome;
}

const std::string& Cliente::getNif() const {
    return nif;
}

const std::string& Cliente::getTelefone() const {
    return telefone;
}

void Cliente::setNif(const std::string& nif) {
    if (!ehNifValido(nif)) {
        throw std::invalid_argument("NIF do cliente deve ter 9 digitos.");
    }
    this->nif = nif;
}

bool Cliente::operator==(const Cliente& outro) const {
    if (!nif.empty() && !outro.nif.empty()) {
        return nif == outro.nif;
    }
    return nome == outro.nome;
}
