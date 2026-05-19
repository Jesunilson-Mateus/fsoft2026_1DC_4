#ifndef PROJECT_HEADERS_MODEL_ENTIDADES_RECEITA_H_
#define PROJECT_HEADERS_MODEL_ENTIDADES_RECEITA_H_

#include "Data.h"
#include <string>

class Receita {
private:
    static int proximoId;
    int id{};
    std::string nomePaciente;
    std::string medicamento;
    Data dataValidade;
    std::string medico;
    bool utilizada{};

    static bool ehNomeValido(const std::string& nome);

public:
    Receita();
    Receita(const std::string& nomePaciente, const std::string& medicamento,
            const Data& dataValidade, const std::string& medico);

    int getId() const;
    const std::string& getNomePaciente() const;
    const std::string& getMedicamento() const;
    const Data& getDataValidade() const;
    const std::string& getMedico() const;
    bool foiUtilizada() const;

    bool ehValida() const;
    bool validar();
    void marcarComoUtilizada();

    bool operator==(const Receita& outra) const;
    bool operator==(int id) const;
};

#endif // PROJECT_HEADERS_MODEL_ENTIDADES_RECEITA_H_
