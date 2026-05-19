//
// Medicamento.h - Especialização de Produto com propriedades farmacêuticas
// Criado para o Sistema de Gestão de Farmácia
//

#ifndef PROJECT_HEADERS_MODEL_ENTIDADES_MEDICAMENTO_H_
#define PROJECT_HEADERS_MODEL_ENTIDADES_MEDICAMENTO_H_

#include "Produto.h"
#include "Data.h"
#include <string>

class Medicamento : public Produto {
private:
    bool requerReceita{};
    std::string dosagem;
    std::string fabricante;
    Data dataValidade;

public:
    Medicamento();
    Medicamento(const std::string& nome, const std::string& categoria,
                double preco, int quantidadeStock,
                bool requerReceita, const std::string& dosagem,
                const std::string& fabricante, const Data& dataValidade,
                const std::string& descricao = "");

    // Getters
    bool getRequerReceita() const;
    const std::string& getDosagem() const;
    const std::string& getFabricante() const;
    const Data& getDataValidade() const;

    // Setters
    void setRequerReceita(bool requerReceita);
    void setDosagem(const std::string& dosagem);
    void setFabricante(const std::string& fabricante);
    void setDataValidade(const Data& dataValidade);

    // Validações
    bool ehValido() const;

    virtual ~Medicamento() = default;
};

#endif // PROJECT_HEADERS_MODEL_ENTIDADES_MEDICAMENTO_H_
