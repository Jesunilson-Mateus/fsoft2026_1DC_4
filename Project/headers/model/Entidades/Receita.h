//
// Receita.h - Documento de autorização médica para medicamentos controlados
// Criado para o Sistema de Gestão de Farmácia
//

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

    // Getters
    int getId() const;
    const std::string& getNomePaciente() const;
    const std::string& getMedicamento() const;
    const Data& getDataValidade() const;
    const std::string& getMedico() const;
    bool foiUtilizada() const;

    // Validações
    bool ehValida() const;
    bool validar();

    // Marca receita como utilizada
    void marcarComoUtilizada();

    // Comparadores
    bool operator==(const Receita& outra) const;
    bool operator==(int id) const;

    virtual ~Receita() = default;
};

#endif // PROJECT_HEADERS_MODEL_ENTIDADES_RECEITA_H_
