#include "Project/headers/controllers/Controller.h"
#include "Project/headers/repo/PharmacyRepositoryMemory.h"
#include "Project/Mock/MockData.h"
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

const string FICHEIRO_STOCK = "stock_persistente.txt";

void limparEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int lerInteiro(const string& mensagem) {
    int valor{};
    while (true) {
        cout << mensagem;
        if (cin >> valor) {
            limparEntrada();
            return valor;
        }
        cout << "Valor invalido. Tente novamente.\n";
        limparEntrada();
    }
}

double lerDouble(const string& mensagem) {
    double valor{};
    while (true) {
        cout << mensagem;
        if (cin >> valor) {
            limparEntrada();
            return valor;
        }
        cout << "Valor invalido. Tente novamente.\n";
        limparEntrada();
    }
}

string lerTexto(const string& mensagem) {
    string valor;
    cout << mensagem;
    getline(cin, valor);
    return valor;
}

bool pediuVoltar(const string& valor) {
    return valor == "v" || valor == "V";
}

bool lerInteiroOpcional(const string& mensagem, int& valor) {
    string entrada;
    while (true) {
        cout << mensagem << " (v para voltar): ";
        getline(cin, entrada);
        if (pediuVoltar(entrada)) {
            return false;
        }

        istringstream stream(entrada);
        if (stream >> valor && stream.eof()) {
            return true;
        }

        cout << "Valor invalido. Tente novamente.\n";
    }
}

bool lerDoubleOpcional(const string& mensagem, double& valor) {
    string entrada;
    while (true) {
        cout << mensagem << " (v para voltar): ";
        getline(cin, entrada);
        if (pediuVoltar(entrada)) {
            return false;
        }

        istringstream stream(entrada);
        if (stream >> valor && stream.eof()) {
            return true;
        }

        cout << "Valor invalido. Tente novamente.\n";
    }
}

bool lerTextoOpcional(const string& mensagem, string& valor) {
    cout << mensagem << " (v para voltar): ";
    getline(cin, valor);
    return !pediuVoltar(valor);
}

bool lerSimNao(const string& mensagem) {
    string resposta;
    while (true) {
        cout << mensagem << " (sim/nao): ";
        getline(cin, resposta);

        if (resposta == "sim" || resposta == "Sim" || resposta == "s" || resposta == "S") {
            return true;
        }
        if (resposta == "nao" || resposta == "Nao" || resposta == "n" || resposta == "N") {
            return false;
        }

        cout << "Resposta invalida. Escreva sim ou nao.\n";
    }
}

bool lerDataOpcional(const string& prefixo, Data& data) {
    int dia{};
    int mes{};
    int ano{};

    if (!lerInteiroOpcional(prefixo + " - dia", dia)) return false;
    if (!lerInteiroOpcional(prefixo + " - mes", mes)) return false;
    if (!lerInteiroOpcional(prefixo + " - ano", ano)) return false;

    data = Data(dia, mes, ano);
    return true;
}

Data lerData(const string& prefixo) {
    int dia = lerInteiro(prefixo + " - dia: ");
    int mes = lerInteiro(prefixo + " - mes: ");
    int ano = lerInteiro(prefixo + " - ano: ");
    return Data(dia, mes, ano);
}

void listarProdutos(const Controller& controller) {
    cout << "\nProdutos em stock\n";
    cout << left << setw(8) << "Opcao" << setw(22) << "Nome" << setw(16) << "Categoria"
         << setw(10) << "Preco" << setw(8) << "Stock" << "Receita\n";

    int opcao = 1;
    for (const auto& produto : controller.listarProdutos()) {
        Medicamento* medicamento = dynamic_cast<Medicamento*>(produto.get());
        cout << left << setw(8) << opcao++
             << setw(22) << produto->getNome()
             << setw(16) << produto->getCategoria()
             << setw(10) << fixed << setprecision(2) << produto->getPreco()
             << setw(8) << produto->getQuantidadeStock()
             << (medicamento != nullptr && medicamento->getRequerReceita() ? "Sim" : "Nao")
             << "\n";
    }
}

void listarReceitas(const Controller& controller) {
    cout << "\nReceitas disponiveis\n";
    cout << left << setw(22) << "Paciente" << setw(22)
         << "Medicamento" << setw(18) << "Codigo da receita" << "Estado\n";

    for (const auto& receita : controller.listarReceitas()) {
        cout << left << setw(22) << receita->getNomePaciente()
             << setw(22) << receita->getMedicamento()
             << setw(18) << receita->getCodigoReceita()
             << (receita->foiUtilizada() ? "Utilizada" : "Disponivel")
             << "\n";
    }
}

Receita* procurarReceitaDisponivel(const Controller& controller, const string& medicamento) {
    for (const auto& receita : controller.listarReceitas()) {
        if (!receita->foiUtilizada() && receita->getMedicamento() == medicamento) {
            return receita.get();
        }
    }
    return nullptr;
}

void listarFuncionarios(const Controller& controller) {
    cout << "\nFuncionarios registados\n";
    cout << left << setw(8) << "Opcao" << setw(24) << "Nome"
         << setw(18) << "Username" << "Cargo\n";

    int opcao = 1;
    for (const auto& funcionario : controller.listarFuncionarios()) {
        cout << left << setw(8) << opcao++
             << setw(24) << funcionario->getNome()
             << setw(18) << funcionario->getUsername()
             << funcionario->getCargo()
             << "\n";
    }
}

void iniciarSessao(Controller& controller) {
    while (controller.getUtilizadorAutenticado() == nullptr) {
        cout << "\nCredenciais de teste: gestora/1234 ou joao/abcd\n";
        string username = lerTexto("Username: ");
        string password = lerTexto("Password: ");

        if (controller.autenticar(username, password) == nullptr) {
            cout << "Credenciais invalidas.\n";
        }
    }

    cout << "Sessao iniciada como "
         << controller.getUtilizadorAutenticado()->getNome()
         << " (" << controller.getUtilizadorAutenticado()->getCargo() << ").\n";
}

void registarVenda(Controller& controller, PharmacyRepositoryMemory& repository) {
    listarProdutos(controller);

    vector<pair<int, int>> itens;
    map<int, int> quantidadesPorProduto;
    bool precisaReceita = false;
    int codigoReceita = 0;
    string nomePacienteReceita;
    while (true) {
        int posicaoProduto{};
        if (!lerInteiroOpcional("\nOpcao do produto (0 para terminar venda)", posicaoProduto)) {
            cout << "Venda cancelada.\n";
            return;
        }
        if (posicaoProduto == 0) break;

        int quantidade{};
        if (!lerInteiroOpcional("Quantidade", quantidade)) {
            cout << "Venda cancelada.\n";
            return;
        }
        if (quantidade <= 0) {
            cout << "Quantidade invalida.\n";
            continue;
        }

        Produto* produto = controller.obterProdutoPorPosicao(posicaoProduto);
        if (produto == nullptr) {
            cout << "Produto nao encontrado.\n";
            continue;
        }

        int quantidadeTotal = quantidadesPorProduto[posicaoProduto] + quantidade;
        if (quantidadeTotal > produto->getQuantidadeStock()) {
            cout << "Falha na venda por falta de stock.\n";
            return;
        }

        Medicamento* medicamento = dynamic_cast<Medicamento*>(produto);
        if (medicamento != nullptr && medicamento->getRequerReceita()) {
            precisaReceita = true;
            cout << "Este medicamento requer receita.\n";
            if (!lerSimNao("A receita e valida?")) {
                cout << "Falha na venda: receita invalida.\n";
                return;
            }

            Receita* receita = procurarReceitaDisponivel(controller, medicamento->getNome());
            if (receita == nullptr) {
                cout << "Falha na venda: nao existe receita disponivel para este medicamento.\n";
                return;
            }

            codigoReceita = receita->getCodigoReceita();
            nomePacienteReceita = receita->getNomePaciente();
        }

        itens.push_back({posicaoProduto, quantidade});
        quantidadesPorProduto[posicaoProduto] = quantidadeTotal;
    }

    if (itens.empty()) {
        cout << "Venda cancelada: nenhum item selecionado.\n";
        return;
    }

    try {
        Venda& venda = controller.registarVenda(itens, Data(19, 5, 2026), codigoReceita);
        repository.guardarStock(FICHEIRO_STOCK);
        cout << "Venda registada com sucesso";
        if (precisaReceita) {
            cout << " em nome de " << nomePacienteReceita;
        }
        cout << ". Total: " << fixed << setprecision(2) << venda.getTotal() << " EUR\n";
    } catch (const exception& erro) {
        cout << "Falha na venda: " << erro.what() << "\n";
    }
}

void gerirStock(Controller& controller, PharmacyRepositoryMemory& repository) {
    listarProdutos(controller);
    int posicaoProduto{};
    int quantidade{};

    if (!lerInteiroOpcional("\nOpcao do produto", posicaoProduto)) {
        cout << "Operacao cancelada.\n";
        return;
    }
    if (!lerInteiroOpcional("Quantidade", quantidade)) {
        cout << "Operacao cancelada.\n";
        return;
    }

    cout << "1 - Adicionar stock\n";
    cout << "2 - Remover stock\n";
    int opcao{};
    if (!lerInteiroOpcional("Opcao", opcao)) {
        cout << "Operacao cancelada.\n";
        return;
    }

    if (opcao == 1) {
        controller.adicionarStock(posicaoProduto, quantidade);
        repository.guardarStock(FICHEIRO_STOCK);
        cout << "Stock adicionado com sucesso.\n";
    } else if (opcao == 2) {
        controller.removerStock(posicaoProduto, quantidade);
        repository.guardarStock(FICHEIRO_STOCK);
        cout << "Stock removido com sucesso.\n";
    } else {
        cout << "Opcao invalida.\n";
    }
}

void adicionarProduto(Controller& controller) {
    string nome;
    string categoria;
    string descricao;
    double preco{};
    int stock{};

    if (!lerTextoOpcional("Nome", nome)) {
        cout << "Adicao cancelada.\n";
        return;
    }
    if (!lerTextoOpcional("Categoria", categoria)) {
        cout << "Adicao cancelada.\n";
        return;
    }
    if (!lerDoubleOpcional("Preco", preco)) {
        cout << "Adicao cancelada.\n";
        return;
    }
    if (!lerInteiroOpcional("Stock inicial", stock)) {
        cout << "Adicao cancelada.\n";
        return;
    }
    if (!lerTextoOpcional("Descricao", descricao)) {
        cout << "Adicao cancelada.\n";
        return;
    }

    cout << "1 - Produto comum\n";
    cout << "2 - Medicamento\n";
    int tipo{};
    if (!lerInteiroOpcional("Tipo", tipo)) {
        cout << "Adicao cancelada.\n";
        return;
    }

    if (tipo == 1) {
        controller.adicionarProduto(nome, categoria, preco, stock, descricao);
    } else if (tipo == 2) {
        int requerReceita{};
        string dosagem;
        string fabricante;
        Data validade;

        if (!lerInteiroOpcional("Requer receita? (1 sim, 0 nao)", requerReceita)) {
            cout << "Adicao cancelada.\n";
            return;
        }
        if (!lerTextoOpcional("Dosagem", dosagem)) {
            cout << "Adicao cancelada.\n";
            return;
        }
        if (!lerTextoOpcional("Fabricante", fabricante)) {
            cout << "Adicao cancelada.\n";
            return;
        }
        if (!lerDataOpcional("Validade", validade)) {
            cout << "Adicao cancelada.\n";
            return;
        }
        controller.adicionarMedicamento(nome, categoria, preco, stock, requerReceita == 1,
                                        dosagem, fabricante, validade, descricao);
    } else {
        cout << "Tipo invalido.\n";
        return;
    }

    cout << "Produto adicionado com sucesso.\n";
}

void adicionarFuncionario(Controller& controller) {
    string nome;
    string username;
    string password;

    if (!lerTextoOpcional("Nome", nome)) {
        cout << "Adicao cancelada.\n";
        return;
    }
    if (!lerTextoOpcional("Username", username)) {
        cout << "Adicao cancelada.\n";
        return;
    }
    if (!lerTextoOpcional("Password", password)) {
        cout << "Adicao cancelada.\n";
        return;
    }

    cout << "1 - Funcionario\n";
    cout << "2 - Gestor\n";
    int tipo{};
    if (!lerInteiroOpcional("Tipo", tipo)) {
        cout << "Adicao cancelada.\n";
        return;
    }

    if (tipo == 1) {
        controller.adicionarFuncionario(nome, username, password);
    } else if (tipo == 2) {
        controller.adicionarGestor(nome, username, password);
    } else {
        cout << "Tipo invalido.\n";
        return;
    }

    cout << "Utilizador criado com sucesso.\n";
}

void adicionarReceita(Controller& controller) {
    string paciente;
    string medicamento;
    string medico;
    int codigo{};

    if (!lerTextoOpcional("Nome do paciente", paciente)) {
        cout << "Adicao cancelada.\n";
        return;
    }
    if (!lerTextoOpcional("Medicamento", medicamento)) {
        cout << "Adicao cancelada.\n";
        return;
    }
    if (!lerInteiroOpcional("Codigo da receita com 5 digitos", codigo)) {
        cout << "Adicao cancelada.\n";
        return;
    }
    if (!lerTextoOpcional("Medico", medico)) {
        cout << "Adicao cancelada.\n";
        return;
    }

    controller.adicionarReceita(paciente, medicamento, codigo, medico);
    cout << "Receita adicionada com sucesso.\n";
}

void mostrarRelatorio(Controller& controller) {
    RelatorioResumo resumo = controller.gerarRelatorioResumo();
    cout << "\nRelatorio resumo\n";
    cout << "Produtos registados: " << resumo.totalProdutos << "\n";
    cout << "Vendas registadas: " << resumo.totalVendas << "\n";
    cout << "Itens vendidos: " << resumo.totalItensVendidos << "\n";
    cout << "Total faturado: " << fixed << setprecision(2) << resumo.totalFaturado << " EUR\n";
}

void mostrarMenu(const Controller& controller) {
    cout << "\n=== Sistema de Gestao de Farmacia ===\n";
    cout << "1 - Listar produtos/stock\n";
    cout << "2 - Registar venda\n";
    cout << "3 - Listar receitas\n";

    if (controller.utilizadorEhGestor()) {
        cout << "4 - Gerir stock\n";
        cout << "5 - Adicionar produto\n";
        cout << "6 - Adicionar funcionario/gestor\n";
        cout << "7 - Adicionar receita\n";
        cout << "8 - Listar funcionarios\n";
        cout << "9 - Relatorio resumo\n";
        cout << "10 - Terminar sessao\n";
    } else {
        cout << "9 - Terminar sessao\n";
    }

    cout << "0 - Sair\n";
}

int main() {
    PharmacyRepositoryMemory repository;
    Controller controller(&repository);
    MockData::carregarDadosIniciais(controller);
    repository.carregarStockGuardado(FICHEIRO_STOCK);

    cout << "Sistema de Gestao de Farmacia\n";

    bool sair = false;
    while (!sair) {
        try {
            if (controller.getUtilizadorAutenticado() == nullptr) {
                iniciarSessao(controller);
            }

            mostrarMenu(controller);
            int opcao = lerInteiro("Opcao: ");

            switch (opcao) {
                case 1:
                    listarProdutos(controller);
                    break;
                case 2:
                    registarVenda(controller, repository);
                    break;
                case 3:
                    listarReceitas(controller);
                    break;
                case 4:
                    gerirStock(controller, repository);
                    break;
                case 5:
                    adicionarProduto(controller);
                    break;
                case 6:
                    adicionarFuncionario(controller);
                    break;
                case 7:
                    adicionarReceita(controller);
                    break;
                case 8:
                    if (controller.utilizadorEhGestor()) {
                        listarFuncionarios(controller);
                    } else {
                        cout << "Opcao invalida.\n";
                    }
                    break;
                case 9:
                    if (controller.utilizadorEhGestor()) {
                        mostrarRelatorio(controller);
                    } else {
                        controller.terminarSessao();
                        cout << "Sessao terminada.\n";
                    }
                    break;
                case 10:
                    if (controller.utilizadorEhGestor()) {
                        controller.terminarSessao();
                        cout << "Sessao terminada.\n";
                    } else {
                        cout << "Opcao invalida.\n";
                    }
                    break;
                case 0:
                    sair = true;
                    break;
                default:
                    cout << "Opcao invalida.\n";
                    break;
            }
        } catch (const exception& erro) {
            cout << "Erro: " << erro.what() << "\n";
        }
    }

    cout << "Programa terminado.\n";
    return 0;
}
