#ifndef PROJECT_HEADERS_MODEL_ENTIDADES_VENDA_H_
#define PROJECT_HEADERS_MODEL_ENTIDADES_VENDA_H_

#include "Cliente.h"
#include "Data.h"
#include "Funcionario.h"
#include "Produto.h"
#include "Receita.h"
#include <string>
#include <vector>

struct ItemVenda {
    Produto* produto{};
    int quantidade{};
    double precoUnitario{};
    double subtotal{};

    ItemVenda(Produto* produto, int quantidade, double precoUnitario);
};

class Venda {
private:
    Data dataVenda;
    Funcionario* funcionario{};
    std::vector<ItemVenda> itens;
    double total{};
    Receita* receita{};
    Cliente* cliente{};

public:
    Venda();
    Venda(const Data& dataVenda, Funcionario* funcionario);

    const Data& getDataVenda() const;
    Funcionario* getFuncionario() const;
    const std::vector<ItemVenda>& getItens() const;
    double getTotal() const;
    Receita* getReceita() const;
    Cliente* getCliente() const;
    const std::string& getNomePaciente() const;

    void adicionarItem(Produto* produto, int quantidade);
    void definirReceita(Receita* receita);
    void definirCliente(Cliente* cliente);
    void calcularTotal();
    bool processarVenda();

    bool operator==(const Venda& outra) const;
};

#endif // PROJECT_HEADERS_MODEL_ENTIDADES_VENDA_H_
