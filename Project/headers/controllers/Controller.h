#ifndef FSOFT2026_1DC_4_CONTROLLER_H
#define FSOFT2026_1DC_4_CONTROLLER_H

#include "../model/Entidades/Funcionario.h"
#include "../model/Entidades/Gestor.h"
#include "../model/Entidades/Medicamento.h"
#include "../model/Entidades/Produto.h"
#include "../model/Entidades/Receita.h"
#include "../model/Entidades/Venda.h"
#include <memory>
#include <string>
#include <vector>

struct RelatorioResumo {
    int totalProdutos{};
    int totalVendas{};
    int totalItensVendidos{};
    double totalFaturado{};
};

class Controller {
private:
    std::vector<std::unique_ptr<Produto>> produtos;
    std::vector<std::unique_ptr<Funcionario>> funcionarios;
    std::vector<std::unique_ptr<Receita>> receitas;
    std::vector<std::unique_ptr<Venda>> vendas;
    Funcionario* utilizadorAutenticado{};

    Produto* procurarProdutoInterno(int id) const;
    Funcionario* procurarFuncionarioInterno(int id) const;
    Receita* procurarReceitaInterna(int id) const;
    void exigirAutenticacao() const;
    void exigirGestor() const;

public:
    Controller();

    Funcionario* autenticar(const std::string& username, const std::string& password);
    void terminarSessao();
    Funcionario* getUtilizadorAutenticado() const;
    bool utilizadorEhGestor() const;

    Produto& adicionarProduto(const std::string& nome, const std::string& categoria,
                              double preco, int quantidadeStock,
                              const std::string& descricao = "");
    Medicamento& adicionarMedicamento(const std::string& nome, const std::string& categoria,
                                      double preco, int quantidadeStock,
                                      bool requerReceita, const std::string& dosagem,
                                      const std::string& fabricante,
                                      const Data& dataValidade,
                                      const std::string& descricao = "");
    Funcionario& adicionarFuncionario(const std::string& nome, const std::string& username,
                                      const std::string& password);
    Gestor& adicionarGestor(const std::string& nome, const std::string& username,
                            const std::string& password);
    Receita& adicionarReceita(const std::string& nomePaciente,
                              const std::string& medicamento,
                              const Data& dataValidade,
                              const std::string& medico);

    Produto* procurarProduto(int id) const;
    Funcionario* procurarFuncionario(int id) const;
    Receita* procurarReceita(int id) const;

    const std::vector<std::unique_ptr<Produto>>& listarProdutos() const;
    const std::vector<std::unique_ptr<Funcionario>>& listarFuncionarios() const;
    const std::vector<std::unique_ptr<Venda>>& listarVendas() const;

    int consultarStock(int produtoId) const;
    void adicionarStock(int produtoId, int quantidade);
    void removerStock(int produtoId, int quantidade);

    Venda& registarVenda(const std::vector<std::pair<int, int>>& itens,
                         const Data& dataVenda,
                         int receitaId = 0);

    RelatorioResumo gerarRelatorioResumo() const;
};

#endif //FSOFT2026_1DC_4_CONTROLLER_H
