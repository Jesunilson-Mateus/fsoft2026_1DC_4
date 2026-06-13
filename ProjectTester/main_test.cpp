#include "../Project/headers/controllers/Controller.h"
#include "../Project/headers/repo/RepositorioFarmaciaMemoria.h"
#include <cassert>
#include <iostream>
#include <stdexcept>

int main() {
    RepositorioFarmaciaMemoria repositorio;
    Controller controller(&repositorio);

    Gestor& gestor = controller.adicionarGestor("Maria Gestora", "gestora", "1234");
    Funcionario& funcionario = controller.adicionarFuncionario("Joao Silva", "joao", "abcd");
    Produto& produto = controller.adicionarProduto("Termometro", "Equipamento", 12.50, 10);
    Medicamento& medicamento = controller.adicionarMedicamento(
        "Antibiotico", "Medicamento", 8.0, 5, true);

    assert(controller.autenticar("joao", "abcd") == &funcionario);
    assert(controller.consultarStock(1) == 10);

    bool bloqueouStock = false;
    try {
        controller.adicionarStock(1, 3);
    } catch (const std::runtime_error&) {
        bloqueouStock = true;
    }
    assert(bloqueouStock);

    Venda& vendaFuncionario = controller.registarVenda(
        {{1, 2}, {2, 1}},
        Data(19, 5, 2026),
        "Ana Paciente",
        true);
    assert(vendaFuncionario.getTotal() == 33.0);
    assert(vendaFuncionario.getCliente() != nullptr);
    assert(vendaFuncionario.getNomePaciente() == "Ana Paciente");
    assert(vendaFuncionario.getReceita() != nullptr);
    assert(vendaFuncionario.getReceita()->getCliente() == vendaFuncionario.getCliente());
    assert(vendaFuncionario.getReceita()->getMedicamento() == medicamento.getNome());
    assert(controller.consultarStock(1) == 8);
    assert(controller.consultarStock(2) == 4);
    assert(controller.listarReceitas().size() == 1);
    assert(controller.listarClientes().size() == 1);
    assert(controller.listarReceitas().front()->foiUtilizada());

    controller.autenticar("gestora", "1234");
    assert(controller.getUtilizadorAutenticado() == &gestor);
    controller.adicionarStock(1, 5);
    assert(controller.consultarStock(1) == 13);

    controller.adicionarFuncionario("Carlos Temporario", "carlos", "temp");
    assert(controller.listarFuncionarios().size() == 3);
    controller.removerFuncionario(3);
    assert(controller.listarFuncionarios().size() == 2);
    assert(controller.autenticar("carlos", "temp") == nullptr);

    controller.autenticar("gestora", "1234");
    bool bloqueouRemoverGestorAutenticado = false;
    try {
        controller.removerFuncionario(1);
    } catch (const std::runtime_error&) {
        bloqueouRemoverGestorAutenticado = true;
    }
    assert(bloqueouRemoverGestorAutenticado);

    RelatorioResumo resumo = controller.gerarRelatorioResumo();
    assert(resumo.totalProdutos == 2);
    assert(resumo.totalVendas == 1);
    assert(resumo.totalItensVendidos == 3);
    assert(resumo.totalFaturado == 33.0);

    std::cout << "Todos os testes passaram com sucesso.\n";
    return 0;
}
