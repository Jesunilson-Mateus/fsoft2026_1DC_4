#ifndef PROJECT_HEADERS_MODEL_ENTIDADES_FARMACIA_H_
#define PROJECT_HEADERS_MODEL_ENTIDADES_FARMACIA_H_

#include "Cliente.h"
#include "Funcionario.h"
#include "Produto.h"
#include "Receita.h"
#include "Venda.h"
#include <memory>
#include <string>
#include <vector>

class Farmacia {
private:
    std::string nome;
    std::vector<std::unique_ptr<Cliente>> clientes;
    std::vector<std::unique_ptr<Produto>> produtos;
    std::vector<std::unique_ptr<Funcionario>> funcionarios;
    std::vector<std::unique_ptr<Receita>> receitas;
    std::vector<std::unique_ptr<Venda>> vendas;

public:
    explicit Farmacia(const std::string& nome = "Farmacia");

    const std::string& getNome() const;
    void setNome(const std::string& nome);

    std::vector<std::unique_ptr<Cliente>>& getClientes();
    std::vector<std::unique_ptr<Produto>>& getProdutos();
    std::vector<std::unique_ptr<Funcionario>>& getFuncionarios();
    std::vector<std::unique_ptr<Receita>>& getReceitas();
    std::vector<std::unique_ptr<Venda>>& getVendas();
    const std::vector<std::unique_ptr<Produto>>& getProdutos() const;

    Funcionario& guardarFuncionario(std::unique_ptr<Funcionario> funcionario);
    void removerFuncionarioPorPosicao(int posicaoFuncionario);
};

#endif // PROJECT_HEADERS_MODEL_ENTIDADES_FARMACIA_H_
