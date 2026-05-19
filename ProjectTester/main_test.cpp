#include "../Project/headers/controllers/Controller.h"
#include <cassert>
#include <stdexcept>

int main() {
    Controller controller;

    Gestor& gestor = controller.adicionarGestor("Maria Gestora", "gestora", "1234");
    Funcionario& funcionario = controller.adicionarFuncionario("Joao Silva", "joao", "abcd");
    Produto& produto = controller.adicionarProduto("Termometro", "Equipamento", 12.50, 10);
    Medicamento& medicamento = controller.adicionarMedicamento(
        "Antibiotico", "Medicamento", 8.0, 5, true, "500mg",
        "Farmalab", Data(1, 1, 2027));
    Receita& receita = controller.adicionarReceita(
        "Ana Paciente", "Antibiotico", Data(1, 1, 2027), "Dra. Costa");

    assert(controller.autenticar("joao", "abcd") == &funcionario);
    assert(controller.consultarStock(produto.getId()) == 10);

    bool bloqueouStock = false;
    try {
        controller.adicionarStock(produto.getId(), 3);
    } catch (const std::runtime_error&) {
        bloqueouStock = true;
    }
    assert(bloqueouStock);

    Venda& vendaFuncionario = controller.registarVenda(
        {{produto.getId(), 2}, {medicamento.getId(), 1}},
        Data(19, 5, 2026),
        receita.getId());
    assert(vendaFuncionario.getTotal() == 33.0);
    assert(controller.consultarStock(produto.getId()) == 8);
    assert(controller.consultarStock(medicamento.getId()) == 4);
    assert(receita.foiUtilizada());

    controller.autenticar("gestora", "1234");
    assert(controller.getUtilizadorAutenticado() == &gestor);
    controller.adicionarStock(produto.getId(), 5);
    assert(controller.consultarStock(produto.getId()) == 13);

    RelatorioResumo resumo = controller.gerarRelatorioResumo();
    assert(resumo.totalProdutos == 2);
    assert(resumo.totalVendas == 1);
    assert(resumo.totalItensVendidos == 3);
    assert(resumo.totalFaturado == 33.0);

    return 0;
}
