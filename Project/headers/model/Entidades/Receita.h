#ifndef PROJECT_HEADERS_MODEL_ENTIDADES_RECEITA_H_
#define PROJECT_HEADERS_MODEL_ENTIDADES_RECEITA_H_

#include "Cliente.h"
#include <string>

class Receita {
private:
    Cliente* cliente{};
    std::string medicamento;
    int codigoReceita{};
    std::string medico;
    bool utilizada{};

    static bool ehNomeValido(const std::string& nome);

public:
    Receita();
    Receita(Cliente* cliente, const std::string& medicamento,
            int codigoReceita, const std::string& medico);

    Cliente* getCliente() const;
    const std::string& getNomePaciente() const;
    const std::string& getMedicamento() const;
    int getCodigoReceita() const;
    const std::string& getMedico() const;
    bool foiUtilizada() const;

    bool ehValida() const;
    bool validarCodigo(int codigo) const;
    void marcarComoUtilizada();

    bool operator==(const Receita& outra) const;
};

#endif // PROJECT_HEADERS_MODEL_ENTIDADES_RECEITA_H_
