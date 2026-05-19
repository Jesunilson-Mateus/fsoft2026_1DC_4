//
// Gestor.cpp - Implementação de Gestor
//

#include "../../headers/model/Entidades/Gestor.h"

using namespace std;

Gestor::Gestor() : Funcionario() {
    this->cargo = "Gestor";
}

Gestor::Gestor(const std::string& nome, const std::string& username,
               const std::string& password)
    : Funcionario(nome, username, password, "Gestor") {}
