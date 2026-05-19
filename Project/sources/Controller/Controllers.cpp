#include "../../headers/controllers/Controller.h"
#include <stdexcept>

Controller::Controller() = default;

Produto* Controller::procurarProdutoInterno(int id) const {
    for (const auto& produto : produtos) {
        if (*produto == id) {
            return produto.get();
        }
    }
    return nullptr;
}

Funcionario* Controller::procurarFuncionarioInterno(int id) const {
    for (const auto& funcionario : funcionarios) {
        if (*funcionario == id) {
            return funcionario.get();
        }
    }
    return nullptr;
}

Receita* Controller::procurarReceitaInterna(int id) const {
    for (const auto& receita : receitas) {
        if (*receita == id) {
            return receita.get();
        }
    }
    return nullptr;
}

void Controller::exigirAutenticacao() const {
    if (utilizadorAutenticado == nullptr) {
        throw std::runtime_error("Operacao requer autenticacao.");
    }
}

void Controller::exigirGestor() const {
    exigirAutenticacao();
    if (!utilizadorEhGestor()) {
        throw std::runtime_error("Operacao permitida apenas ao gestor.");
    }
}

Funcionario* Controller::autenticar(const std::string& username, const std::string& password) {
    for (const auto& funcionario : funcionarios) {
        if (funcionario->autenticar(username, password)) {
            utilizadorAutenticado = funcionario.get();
            return utilizadorAutenticado;
        }
    }

    utilizadorAutenticado = nullptr;
    return nullptr;
}

void Controller::terminarSessao() {
    utilizadorAutenticado = nullptr;
}

Funcionario* Controller::getUtilizadorAutenticado() const {
    return utilizadorAutenticado;
}

bool Controller::utilizadorEhGestor() const {
    return dynamic_cast<Gestor*>(utilizadorAutenticado) != nullptr;
}

Produto& Controller::adicionarProduto(const std::string& nome, const std::string& categoria,
                                      double preco, int quantidadeStock,
                                      const std::string& descricao) {
    produtos.push_back(std::unique_ptr<Produto>(
        new Produto(nome, categoria, preco, quantidadeStock, descricao)));
    return *produtos.back();
}

Medicamento& Controller::adicionarMedicamento(const std::string& nome, const std::string& categoria,
                                              double preco, int quantidadeStock,
                                              bool requerReceita, const std::string& dosagem,
                                              const std::string& fabricante,
                                              const Data& dataValidade,
                                              const std::string& descricao) {
    produtos.push_back(std::unique_ptr<Produto>(
        new Medicamento(nome, categoria, preco, quantidadeStock, requerReceita,
                        dosagem, fabricante, dataValidade, descricao)));
    return static_cast<Medicamento&>(*produtos.back());
}

Funcionario& Controller::adicionarFuncionario(const std::string& nome,
                                              const std::string& username,
                                              const std::string& password) {
    funcionarios.push_back(std::unique_ptr<Funcionario>(
        new Funcionario(nome, username, password, "Funcionario")));
    return *funcionarios.back();
}

Gestor& Controller::adicionarGestor(const std::string& nome,
                                    const std::string& username,
                                    const std::string& password) {
    funcionarios.push_back(std::unique_ptr<Funcionario>(
        new Gestor(nome, username, password)));
    return static_cast<Gestor&>(*funcionarios.back());
}

Receita& Controller::adicionarReceita(const std::string& nomePaciente,
                                      const std::string& medicamento,
                                      const Data& dataValidade,
                                      const std::string& medico) {
    receitas.push_back(std::unique_ptr<Receita>(
        new Receita(nomePaciente, medicamento, dataValidade, medico)));
    return *receitas.back();
}

Produto* Controller::procurarProduto(int id) const {
    return procurarProdutoInterno(id);
}

Funcionario* Controller::procurarFuncionario(int id) const {
    return procurarFuncionarioInterno(id);
}

Receita* Controller::procurarReceita(int id) const {
    return procurarReceitaInterna(id);
}

const std::vector<std::unique_ptr<Produto>>& Controller::listarProdutos() const {
    return produtos;
}

const std::vector<std::unique_ptr<Funcionario>>& Controller::listarFuncionarios() const {
    return funcionarios;
}

const std::vector<std::unique_ptr<Venda>>& Controller::listarVendas() const {
    return vendas;
}

int Controller::consultarStock(int produtoId) const {
    exigirAutenticacao();
    Produto* produto = procurarProdutoInterno(produtoId);
    if (produto == nullptr) {
        throw std::invalid_argument("Produto nao encontrado.");
    }
    return produto->getQuantidadeStock();
}

void Controller::adicionarStock(int produtoId, int quantidade) {
    exigirGestor();
    Produto* produto = procurarProdutoInterno(produtoId);
    if (produto == nullptr) {
        throw std::invalid_argument("Produto nao encontrado.");
    }
    produto->adicionarStock(quantidade);
}

void Controller::removerStock(int produtoId, int quantidade) {
    exigirGestor();
    Produto* produto = procurarProdutoInterno(produtoId);
    if (produto == nullptr) {
        throw std::invalid_argument("Produto nao encontrado.");
    }
    produto->removerStock(quantidade);
}

Venda& Controller::registarVenda(const std::vector<std::pair<int, int>>& itens,
                                 const Data& dataVenda,
                                 int receitaId) {
    exigirAutenticacao();
    if (itens.empty()) {
        throw std::invalid_argument("Venda deve conter pelo menos um item.");
    }

    std::unique_ptr<Venda> venda(new Venda(dataVenda, utilizadorAutenticado));
    Receita* receita = receitaId > 0 ? procurarReceitaInterna(receitaId) : nullptr;

    for (const auto& item : itens) {
        Produto* produto = procurarProdutoInterno(item.first);
        if (produto == nullptr) {
            throw std::invalid_argument("Produto nao encontrado.");
        }

        Medicamento* medicamento = dynamic_cast<Medicamento*>(produto);
        if (medicamento != nullptr && medicamento->getRequerReceita()) {
            if (receita == nullptr) {
                throw std::runtime_error("Medicamento requer receita valida.");
            }
            if (receita->getMedicamento() != medicamento->getNome()) {
                throw std::runtime_error("Receita nao corresponde ao medicamento vendido.");
            }
            receita->validar();
            venda->definirReceita(receita);
        }

        venda->adicionarItem(produto, item.second);
    }

    venda->processarVenda();
    if (receita != nullptr) {
        receita->marcarComoUtilizada();
    }

    vendas.push_back(std::move(venda));
    return *vendas.back();
}

RelatorioResumo Controller::gerarRelatorioResumo() const {
    exigirGestor();
    RelatorioResumo resumo;
    resumo.totalProdutos = static_cast<int>(produtos.size());
    resumo.totalVendas = static_cast<int>(vendas.size());

    for (const auto& venda : vendas) {
        resumo.totalFaturado += venda->getTotal();
        for (const auto& item : venda->getItens()) {
            resumo.totalItensVendidos += item.quantidade;
        }
    }

    return resumo;
}
