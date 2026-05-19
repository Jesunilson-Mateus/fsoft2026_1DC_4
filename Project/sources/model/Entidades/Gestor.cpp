#include "Gestor.h"

Gestor::Gestor() : Funcionario() {
    cargo = "Gestor";
}

Gestor::Gestor(const std::string& nome, const std::string& username,
               const std::string& password)
    : Funcionario(nome, username, password, "Gestor") {}

bool Gestor::podeGerirStock() const {
    return true;
}

bool Gestor::podeGerirFuncionarios() const {
    return true;
}

bool Gestor::podeConsultarRelatorios() const {
    return true;
}

bool Gestor::podeGerirProdutos() const {
    return true;
}
