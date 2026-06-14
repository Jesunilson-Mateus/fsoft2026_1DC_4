#include "TestUtils.h"

namespace {

void controller_controla_permissoes_de_stock() {
    AmbienteController ambiente;
    Gestor& gestor = ambiente.controller.adicionarGestor("Maria Gestora", "gestora", "1234");
    Funcionario& funcionario = ambiente.controller.adicionarFuncionario("Joao Silva", "joao", "abcd");
    ambiente.controller.adicionarProduto("Termometro", "Equipamento", 12.50, 10);

    confirmar(ambiente.controller.autenticar("joao", "abcd") == &funcionario,
              "Funcionario deve autenticar.");
    confirmar(ambiente.controller.consultarStock(1) == 10,
              "Funcionario autenticado deve consultar stock.");
    confirmarExcecao<std::runtime_error>(
        [&ambiente]() { ambiente.controller.adicionarStock(1, 3); },
        "Funcionario sem cargo de gestor nao deve adicionar stock.");

    confirmar(ambiente.controller.autenticar("gestora", "1234") == &gestor,
              "Gestor deve autenticar.");
    ambiente.controller.adicionarStock(1, 5);
    confirmar(ambiente.controller.consultarStock(1) == 15,
              "Gestor deve conseguir adicionar stock.");
}

void controller_remove_funcionario_com_regras_de_gestor() {
    AmbienteController ambiente;
    ambiente.controller.adicionarGestor("Maria Gestora", "gestora", "1234");
    ambiente.controller.adicionarFuncionario("Joao Silva", "joao", "abcd");
    ambiente.controller.adicionarFuncionario("Carlos Temporario", "carlos", "temp");

    ambiente.controller.autenticar("gestora", "1234");
    confirmar(ambiente.controller.listarFuncionarios().size() == 3,
              "Devem existir tres funcionarios antes da remocao.");

    ambiente.controller.removerFuncionario(3);
    confirmar(ambiente.controller.listarFuncionarios().size() == 2,
              "Remover funcionario deve reduzir a lista.");
    confirmar(ambiente.controller.autenticar("carlos", "temp") == nullptr,
              "Funcionario removido nao deve autenticar.");

    ambiente.controller.autenticar("gestora", "1234");
    confirmarExcecao<std::runtime_error>(
        [&ambiente]() { ambiente.controller.removerFuncionario(1); },
        "Gestor autenticado nao deve remover a si proprio.");
}

} // namespace

std::vector<TestCase> obterTestesController() {
    return {
        {"Controller: controla permissoes de stock", controller_controla_permissoes_de_stock},
        {"Controller: remove funcionario com regras de gestor",
         controller_remove_funcionario_com_regras_de_gestor},
    };
}
