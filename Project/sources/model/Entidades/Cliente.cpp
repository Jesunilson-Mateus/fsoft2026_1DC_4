#include "Cliente.h"
#include <stdexcept>

Cliente::Cliente() : nome(""), nif(""), telefone("") {}

Cliente::Cliente(const std::string& nome,
                 const std::string& nif,
                 const std::string& telefone)
        : nome(nome), nif(nif), telefone(telefone) {
    if (nome.length() < 3) {
        throw std::invalid_argument("Nome do cliente deve ter pelo menos 3 caracteres.");
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

bool Cliente::operator==(const Cliente& outro) const {
    if (!nif.empty() && !outro.nif.empty()) {
        return nif == outro.nif;
    }
    return nome == outro.nome;
}
