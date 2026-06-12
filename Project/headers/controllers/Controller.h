#ifndef FSOFT2026_1DC_4_CONTROLLER_H
#define FSOFT2026_1DC_4_CONTROLLER_H

#include "../model/Entidades/Funcionario.h"
#include "../model/Entidades/Gestor.h"
#include "../model/Entidades/Medicamento.h"
#include "../model/Entidades/Produto.h"
#include "../model/Entidades/Receita.h"
#include "../model/Entidades/Venda.h"
#include "../repo/IRepositorioFarmacia.h"
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
    IRepositorioFarmacia* repositorio{};
    Funcionario* utilizadorAutenticado{};

    Cliente* procurarClientePorNomeInterna(const std::string& nome) const;
    Cliente& obterOuCriarClienteInterno(const std::string& nome);
    Produto* obterProdutoPorPosicaoInterna(int posicao) const;
    Receita* procurarReceitaPorCodigoInterna(int codigo) const;
    int gerarCodigoReceitaInterno() const;
    void exigirAutenticacao() const;
    void exigirGestor() const;

public:
    explicit Controller(IRepositorioFarmacia* repositorio);

    Funcionario* autenticar(const std::string& username, const std::string& password);
    void terminarSessao();
    Funcionario* getUtilizadorAutenticado() const;
    bool utilizadorEhGestor() const;

    Produto& adicionarProduto(const std::string& nome, const std::string& categoria,
                              double preco, int quantidadeStock,
                              const std::string& descricao = "");
    Medicamento& adicionarMedicamento(const std::string& nome, const std::string& categoria,
                                      double preco, int quantidadeStock,
                                      bool requerReceita,
                                      const std::string& descricao = "");
    Funcionario& adicionarFuncionario(const std::string& nome, const std::string& username,
                                      const std::string& password);
    Gestor& adicionarGestor(const std::string& nome, const std::string& username,
                            const std::string& password);
    void removerFuncionario(int posicaoFuncionario);
    Cliente& adicionarCliente(const std::string& nome,
                              const std::string& nif = "",
                              const std::string& telefone = "");
    Receita& adicionarReceita(const std::string& nomeCliente,
                              const std::string& medicamento,
                              int codigoReceita,
                              const std::string& medico);

    Produto* obterProdutoPorPosicao(int posicao) const;

    const std::vector<std::unique_ptr<Produto>>& listarProdutos() const;
    const std::vector<std::unique_ptr<Cliente>>& listarClientes() const;
    const std::vector<std::unique_ptr<Funcionario>>& listarFuncionarios() const;
    const std::vector<std::unique_ptr<Receita>>& listarReceitas() const;
    const std::vector<std::unique_ptr<Venda>>& listarVendas() const;

    int consultarStock(int posicaoProduto) const;
    void adicionarStock(int posicaoProduto, int quantidade);
    void removerStock(int posicaoProduto, int quantidade);
    void carregarStockGuardado(const std::string& ficheiroStock);
    void guardarStockAtual(const std::string& ficheiroStock) const;

    Venda& registarVenda(const std::vector<std::pair<int, int>>& itens,
                         const Data& dataVenda,
                         const std::string& nomeCliente,
                         bool receitaValidada = false);

    RelatorioResumo gerarRelatorioResumo() const;
};

#endif //FSOFT2026_1DC_4_CONTROLLER_H
