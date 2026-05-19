//
// Gestor.h - Funcionário com permissões administrativas
// Criado para o Sistema de Gestão de Farmácia
//

#ifndef PROJECT_HEADERS_MODEL_ENTIDADES_GESTOR_H_
#define PROJECT_HEADERS_MODEL_ENTIDADES_GESTOR_H_

#include "Funcionario.h"

class Gestor : public Funcionario {
public:
    Gestor();
    Gestor(const std::string& nome, const std::string& username,
           const std::string& password);

    // Permissões específicas do Gestor
    bool podeGerirStock() const { return true; }
    bool podeGerirFuncionarios() const { return true; }
    bool podeConsultarRelatorios() const { return true; }
    bool podeGerirProdutos() const { return true; }

    virtual ~Gestor() = default;
};

#endif // PROJECT_HEADERS_MODEL_ENTIDADES_GESTOR_H_
