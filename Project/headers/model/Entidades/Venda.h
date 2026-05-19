//
// Venda.h - Registro de transações de venda
// Criado para o Sistema de Gestão de Farmácia
//

#ifndef PROJECT_HEADERS_MODEL_ENTIDADES_VENDA_H_
#define PROJECT_HEADERS_MODEL_ENTIDADES_VENDA_H_

#include "Data.h"
#include "Produto.h"
#include "Medicamento.h"
#include "Funcionario.h"
#include "Receita.h"
#include <vector>
#include <memory>

struct ItemVenda {
    Produto* produto;
    int quantidade;
    double precoUnitario;
    double subtotal;

    ItemVenda(Produto* prod, int qtd, double preco)
        : produto(prod), quantidade(qtd), precoUnitario(preco),
          subtotal(qtd * preco) {}
};

class Venda {
private:
    static int proximoId;
    int idVenda{};
    Data dataVenda;
    Funcionario* funcionario{};
    std::vector<ItemVenda> itens;
    double total{};
    Receita* receita{}; // Opcional, apenas para medicamentos controlados

public:
    Venda();
    Venda(const Data& dataVenda, Funcionario* funcionario);

    // Getters
    int getId() const;
    const Data& getDataVenda() const;
    Funcionario* getFuncionario() const;
    const std::vector<ItemVenda>& getItens() const;
    double getTotal() const;
    Receita* getReceita() const;

    // Adicionar itens
    void adicionarItem(Produto* produto, int quantidade);

    // Gestão de receita
    void definirReceita(Receita* receita);

    // Cálculos
    void calcularTotal();
    double obterSubtotal() const;

    // Confirmação
    bool processarVenda();

    // Comparadores
    bool operator==(const Venda& outra) const;
    bool operator==(int id) const;

    virtual ~Venda();
};

#endif // PROJECT_HEADERS_MODEL_ENTIDADES_VENDA_H_
