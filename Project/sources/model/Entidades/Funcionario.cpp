#include "Funcionario.h"
#include <stdexcept>

bool Funcionario::ehNomeValido(const std::string& nome) {
    return nome.length() >= 3;
}

bool Funcionario::ehUsernameValido(const std::string& username) {
    return username.length() >= 3 && username.length() <= 20;
}

Funcionario::Funcionario()
    : nome(""), username(""), password(""), cargo("Funcionario") {}

Funcionario::Funcionario(const std::string& nome, const std::string& username,
                         const std::string& password, const std::string& cargo)
    : cargo(cargo) {
    if (!ehNomeValido(nome)) {
        throw std::invalid_argument("Nome deve ter pelo menos 3 caracteres.");
    }
    if (!ehUsernameValido(username)) {
        throw std::invalid_argument("Username deve ter entre 3 e 20 caracteres.");
    }
    if (password.empty()) {
        throw std::invalid_argument("Password nao pode estar vazia.");
    }

    this->nome = nome;
    this->username = username;
    this->password = password;
}

const std::string& Funcionario::getNome() const {
    return nome;
}

const std::string& Funcionario::getUsername() const {
    return username;
}

const std::string& Funcionario::getPassword() const {
    return password;
}

const std::string& Funcionario::getCargo() const {
    return cargo;
}

void Funcionario::setNome(const std::string& nome) {
    if (!ehNomeValido(nome)) {
        throw std::invalid_argument("Nome invalido.");
    }
    this->nome = nome;
}

void Funcionario::setPassword(const std::string& password) {
    if (password.empty()) {
        throw std::invalid_argument("Password nao pode estar vazia.");
    }
    this->password = password;
}

bool Funcionario::autenticar(const std::string& username, const std::string& password) const {
    return this->username == username && this->password == password;
}

bool Funcionario::operator==(const std::string& username) const {
    return this->username == username;
}
