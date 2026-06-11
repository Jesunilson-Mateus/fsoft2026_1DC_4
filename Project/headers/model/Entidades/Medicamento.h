#ifndef PROJECT_HEADERS_MODEL_ENTIDADES_MEDICAMENTO_H_
#define PROJECT_HEADERS_MODEL_ENTIDADES_MEDICAMENTO_H_

#include "Produto.h"

class Medicamento : public Produto {
private:
    bool requerReceita{};

public:
    Medicamento();
    Medicamento(const std::string& nome, const std::string& categoria,
                double preco, int quantidadeStock, bool requerReceita,
                const std::string& descricao = "");

    bool getRequerReceita() const;

    void setRequerReceita(bool requerReceita);
};

#endif // PROJECT_HEADERS_MODEL_ENTIDADES_MEDICAMENTO_H_
