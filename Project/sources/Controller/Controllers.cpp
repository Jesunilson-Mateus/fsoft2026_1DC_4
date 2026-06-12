#include "../../headers/controllers/Controller.h"
#include <stdexcept>

Controller::Controller(IRepositorioFarmacia* repositorio) : repositorio(repositorio) {
    if (repositorio == nullptr) {
        throw std::invalid_argument("Repositorio nao pode ser nulo.");
    }
}

Cliente* Controller::procurarClientePorNomeInterna(const std::string& nome) const {
    auto& clientes = repositorio->getClientes();
    for (const auto& cliente : clientes) {
        if (cliente->getNome() == nome) {
            return cliente.get();
        }
    }
    return nullptr;
}

Cliente& Controller::obterOuCriarClienteInterno(const std::string& nome) {
    Cliente* cliente = procurarClientePorNomeInterna(nome);
    if (cliente != nullptr) {
        return *cliente;
    }
    return adicionarCliente(nome);
}

Produto* Controller::obterProdutoPorPosicaoInterna(int posicao) const {
    auto& produtos = repositorio->getProdutos();
    if (posicao < 1 || posicao > static_cast<int>(produtos.size())) {
        return nullptr;
    }
    return produtos[static_cast<size_t>(posicao - 1)].get();
}

Receita* Controller::procurarReceitaPorCodigoInterna(int codigo) const {
    auto& receitas = repositorio->getReceitas();
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
    auto& funcionarios = repositorio->getFuncionarios();
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
    auto& produtos = repositorio->getProdutos();
    produtos.push_back(std::unique_ptr<Produto>(
        new Produto(nome, categoria, preco, quantidadeStock, descricao)));
    return *produtos.back();
}

Medicamento& Controller::adicionarMedicamento(const std::string& nome, const std::string& categoria,
                                              double preco, int quantidadeStock,
                                              bool requerReceita,
                                              const std::string& descricao) {
    auto& produtos = repositorio->getProdutos();
    produtos.push_back(std::unique_ptr<Produto>(
        new Medicamento(nome, categoria, preco, quantidadeStock, requerReceita,
                        descricao)));
    return static_cast<Medicamento&>(*produtos.back());
}

Funcionario& Controller::adicionarFuncionario(const std::string& nome,
                                              const std::string& username,
                                              const std::string& password) {
    return repositorio->guardarFuncionario(std::unique_ptr<Funcionario>(
        new Funcionario(nome, username, password, "Funcionario")));
}

Gestor& Controller::adicionarGestor(const std::string& nome,
                                    const std::string& username,
                                    const std::string& password) {
    Funcionario& funcionario = repositorio->guardarFuncionario(
        std::unique_ptr<Funcionario>(new Gestor(nome, username, password)));
    return static_cast<Gestor&>(funcionario);
}

void Controller::removerFuncionario(int posicaoFuncionario) {
    exigirGestor();

    auto& funcionarios = repositorio->getFuncionarios();
    if (posicaoFuncionario < 1 || posicaoFuncionario > static_cast<int>(funcionarios.size())) {
        throw std::invalid_argument("Funcionario nao encontrado.");
    }

    if (funcionarios[static_cast<size_t>(posicaoFuncionario - 1)].get() == utilizadorAutenticado) {
        throw std::runtime_error("Gestor autenticado nao pode ser removido durante a sessao.");
    }

    repositorio->removerFuncionarioPorPosicao(posicaoFuncionario);
}

Cliente& Controller::adicionarCliente(const std::string& nome,
                                      const std::string& nif,
                                      const std::string& telefone) {
    Cliente* clienteExistente = procurarClientePorNomeInterna(nome);
    if (clienteExistente != nullptr) {
        return *clienteExistente;
    }

    auto& clientes = repositorio->getClientes();
    clientes.push_back(std::unique_ptr<Cliente>(new Cliente(nome, nif, telefone)));
    return *clientes.back();
}

Receita& Controller::adicionarReceita(const std::string& nomeCliente,
                                      const std::string& medicamento,
                                      int codigoReceita,
                                      const std::string& medico) {
    Cliente& cliente = obterOuCriarClienteInterno(nomeCliente);
    auto& receitas = repositorio->getReceitas();
    receitas.push_back(std::unique_ptr<Receita>(
        new Receita(&cliente, medicamento, codigoReceita, medico)));
    return *receitas.back();
}

Produto* Controller::obterProdutoPorPosicao(int posicao) const {
    return obterProdutoPorPosicaoInterna(posicao);
}

const std::vector<std::unique_ptr<Produto>>& Controller::listarProdutos() const {
    return repositorio->getProdutos();
}

const std::vector<std::unique_ptr<Cliente>>& Controller::listarClientes() const {
    return repositorio->getClientes();
}

const std::vector<std::unique_ptr<Funcionario>>& Controller::listarFuncionarios() const {
    return repositorio->getFuncionarios();
}

const std::vector<std::unique_ptr<Receita>>& Controller::listarReceitas() const {
    return repositorio->getReceitas();
}

const std::vector<std::unique_ptr<Venda>>& Controller::listarVendas() const {
    return repositorio->getVendas();
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

void Controller::carregarStockGuardado(const std::string& ficheiroStock) {
    repositorio->carregarStockGuardado(ficheiroStock);
}

void Controller::guardarStockAtual(const std::string& ficheiroStock) const {
    repositorio->guardarStock(ficheiroStock);
}

Venda& Controller::registarVenda(const std::vector<std::pair<int, int>>& itens,
                                 const Data& dataVenda,
                                 const std::string& nomeCliente,
                                 bool receitaValidada) {
    exigirAutenticacao();
    if (itens.empty()) {
        throw std::invalid_argument("Venda deve conter pelo menos um item.");
    }
    Cliente& cliente = obterOuCriarClienteInterno(nomeCliente);

    std::unique_ptr<Venda> venda(new Venda(dataVenda, utilizadorAutenticado));
    venda->definirCliente(&cliente);
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
        receita = &adicionarReceita(cliente.getNome(), medicamentoDaReceita,
                                    gerarCodigoReceitaInterno(),
                                    "Receita validada na venda");
        venda->definirReceita(receita);
    }

    venda->processarVenda();
    if (receitaFoiNecessaria && receita != nullptr) {
        receita->marcarComoUtilizada();
    }

    auto& vendas = repositorio->getVendas();
    vendas.push_back(std::move(venda));
    return *vendas.back();
}

RelatorioResumo Controller::gerarRelatorioResumo() const {
    exigirGestor();
    RelatorioResumo resumo;
    auto& produtos = repositorio->getProdutos();
    auto& vendas = repositorio->getVendas();
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
