#include "../../headers/controllers/Controller.h"
#include <stdexcept>

Controller::Controller(IPharmacyRepository* repository) : repository(repository) {
    if (repository == nullptr) {
        throw std::invalid_argument("Repositorio nao pode ser nulo.");
    }
}

Produto* Controller::obterProdutoPorPosicaoInterna(int posicao) const {
    auto& produtos = repository->getProdutos();
    if (posicao < 1 || posicao > static_cast<int>(produtos.size())) {
        return nullptr;
    }
    return produtos[static_cast<size_t>(posicao - 1)].get();
}

Receita* Controller::procurarReceitaPorCodigoInterna(int codigo) const {
    auto& receitas = repository->getReceitas();
    for (const auto& receita : receitas) {
        if (receita->getCodigoReceita() == codigo) {
            return receita.get();
        }
    }
    return nullptr;
}

int Controller::gerarCodigoReceitaInterno() const {
    int codigo = 10000;
    while (procurarReceitaPorCodigoInterna(codigo) != nullptr && codigo <= 99999) {
        ++codigo;
    }
    if (codigo > 99999) {
        throw std::runtime_error("Nao foi possivel gerar codigo de receita.");
    }
    return codigo;
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
    auto& funcionarios = repository->getFuncionarios();
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
    auto& produtos = repository->getProdutos();
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
    auto& produtos = repository->getProdutos();
    produtos.push_back(std::unique_ptr<Produto>(
        new Medicamento(nome, categoria, preco, quantidadeStock, requerReceita,
                        dosagem, fabricante, dataValidade, descricao)));
    return static_cast<Medicamento&>(*produtos.back());
}

Funcionario& Controller::adicionarFuncionario(const std::string& nome,
                                              const std::string& username,
                                              const std::string& password) {
    auto& funcionarios = repository->getFuncionarios();
    funcionarios.push_back(std::unique_ptr<Funcionario>(
        new Funcionario(nome, username, password, "Funcionario")));
    return *funcionarios.back();
}

Gestor& Controller::adicionarGestor(const std::string& nome,
                                    const std::string& username,
                                    const std::string& password) {
    auto& funcionarios = repository->getFuncionarios();
    funcionarios.push_back(std::unique_ptr<Funcionario>(
        new Gestor(nome, username, password)));
    return static_cast<Gestor&>(*funcionarios.back());
}

Receita& Controller::adicionarReceita(const std::string& nomePaciente,
                                      const std::string& medicamento,
                                      int codigoReceita,
                                      const std::string& medico) {
    auto& receitas = repository->getReceitas();
    receitas.push_back(std::unique_ptr<Receita>(
        new Receita(nomePaciente, medicamento, codigoReceita, medico)));
    return *receitas.back();
}

Produto* Controller::obterProdutoPorPosicao(int posicao) const {
    return obterProdutoPorPosicaoInterna(posicao);
}

const std::vector<std::unique_ptr<Produto>>& Controller::listarProdutos() const {
    return repository->getProdutos();
}

const std::vector<std::unique_ptr<Funcionario>>& Controller::listarFuncionarios() const {
    return repository->getFuncionarios();
}

const std::vector<std::unique_ptr<Receita>>& Controller::listarReceitas() const {
    return repository->getReceitas();
}

const std::vector<std::unique_ptr<Venda>>& Controller::listarVendas() const {
    return repository->getVendas();
}

int Controller::consultarStock(int posicaoProduto) const {
    exigirAutenticacao();
    Produto* produto = obterProdutoPorPosicaoInterna(posicaoProduto);
    if (produto == nullptr) {
        throw std::invalid_argument("Produto nao encontrado.");
    }
    return produto->getQuantidadeStock();
}

void Controller::adicionarStock(int posicaoProduto, int quantidade) {
    exigirGestor();
    Produto* produto = obterProdutoPorPosicaoInterna(posicaoProduto);
    if (produto == nullptr) {
        throw std::invalid_argument("Produto nao encontrado.");
    }
    produto->adicionarStock(quantidade);
}

void Controller::removerStock(int posicaoProduto, int quantidade) {
    exigirGestor();
    Produto* produto = obterProdutoPorPosicaoInterna(posicaoProduto);
    if (produto == nullptr) {
        throw std::invalid_argument("Produto nao encontrado.");
    }
    produto->removerStock(quantidade);
}

Venda& Controller::registarVenda(const std::vector<std::pair<int, int>>& itens,
                                 const Data& dataVenda,
                                 const std::string& nomePaciente,
                                 bool receitaValidada) {
    exigirAutenticacao();
    if (itens.empty()) {
        throw std::invalid_argument("Venda deve conter pelo menos um item.");
    }
    if (nomePaciente.length() < 3) {
        throw std::invalid_argument("Nome do paciente deve ter pelo menos 3 caracteres.");
    }

    std::unique_ptr<Venda> venda(new Venda(dataVenda, utilizadorAutenticado));
    venda->definirNomePaciente(nomePaciente);
    Receita* receita = nullptr;
    bool receitaFoiNecessaria = false;
    std::string medicamentoDaReceita;

    for (const auto& item : itens) {
        Produto* produto = obterProdutoPorPosicaoInterna(item.first);
        if (produto == nullptr) {
            throw std::invalid_argument("Produto nao encontrado.");
        }

        Medicamento* medicamento = dynamic_cast<Medicamento*>(produto);
        if (medicamento != nullptr && medicamento->getRequerReceita()) {
            receitaFoiNecessaria = true;
            if (!receitaValidada) {
                throw std::runtime_error("Medicamento requer receita valida.");
            }
            if (medicamentoDaReceita.empty()) {
                medicamentoDaReceita = medicamento->getNome();
            }
        }

        venda->adicionarItem(produto, item.second);
    }

    if (receitaFoiNecessaria) {
        receita = &adicionarReceita(nomePaciente, medicamentoDaReceita,
                                    gerarCodigoReceitaInterno(),
                                    "Receita validada na venda");
        venda->definirReceita(receita);
    }

    venda->processarVenda();
    if (receitaFoiNecessaria && receita != nullptr) {
        receita->marcarComoUtilizada();
    }

    auto& vendas = repository->getVendas();
    vendas.push_back(std::move(venda));
    return *vendas.back();
}

RelatorioResumo Controller::gerarRelatorioResumo() const {
    exigirGestor();
    RelatorioResumo resumo;
    auto& produtos = repository->getProdutos();
    auto& vendas = repository->getVendas();
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
