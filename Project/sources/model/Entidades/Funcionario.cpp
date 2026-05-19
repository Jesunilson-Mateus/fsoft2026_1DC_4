//
// Funcionario.cpp - Implementação de Funcionario
//

#include "../../headers/model/Entidades/Funcionario.h"
#include <stdexcept>

using namespace std;

int Funcionario::proximoId = 1000;

bool Funcionario::ehNomeValido(const std::string& nome) {
    return nome.length() >= 3;
}

bool Funcionario::ehUsernameValido(const std::string& username) {
    return username.length() >= 3 && username.length() <= 20;
}

Funcionario::Funcionario() 
    : id(++proximoId), nome(""), username(""), password(""), cargo("Funcionário") {}

Funcionario::Funcionario(const std::string& nome, const std::string& username,
                         const std::string& password, const std::string& cargo)
    : id(++proximoId) {
    if (!ehNomeValido(nome)) {
        throw invalid_argument("Nome deve ter pelo menos 3 caracteres.");
    }
    if (!ehUsernameValido(username)) {
        throw invalid_argument("Username deve ter entre 3 e 20 caracteres.");
    }
    if (password.empty()) {
        throw invalid_argument("Password não pode estar vazia.");
    }

    this->nome = nome;
    this->username = username;
    this->password = password;
    this->cargo = cargo;
}

int Funcionario::getId() const {
    return id;
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
    if (ehNomeValido(nome)) {
        this->nome = nome;
    } else {
        throw invalid_argument("Nome inválido.");
    }
}

void Funcionario::setPassword(const std::string& password) {
    if (!password.empty()) {
        this->password = password;
    } else {
        throw invalid_argument("Password não pode estar vazia.");
    }
}

bool Funcionario::autenticar(const std::string& username, const std::string& password) const {
    return (this->username == username && this->password == password);
}

bool Funcionario::operator==(const Funcionario& outro) const {
    return this->id == outro.id;
}

bool Funcionario::operator==(int id) const {
    return this->id == id;
}

bool Funcionario::operator==(const std::string& username) const {
    return this->username == username;
}
