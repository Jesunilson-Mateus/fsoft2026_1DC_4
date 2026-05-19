#ifndef PROJECT_HEADERS_MODEL_ENTIDADES_GESTOR_H_
#define PROJECT_HEADERS_MODEL_ENTIDADES_GESTOR_H_

#include "Funcionario.h"

class Gestor : public Funcionario {
public:
    Gestor();
    Gestor(const std::string& nome, const std::string& username,
           const std::string& password);

    bool podeGerirStock() const;
    bool podeGerirFuncionarios() const;
    bool podeConsultarRelatorios() const;
    bool podeGerirProdutos() const;
};

#endif // PROJECT_HEADERS_MODEL_ENTIDADES_GESTOR_H_
