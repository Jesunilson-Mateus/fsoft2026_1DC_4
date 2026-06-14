#include "TestUtils.h"

namespace {

void venda_com_receita_cria_cliente_receita_e_atualiza_stock() {
    AmbienteController ambiente;
    ambiente.controller.adicionarGestor("Maria Gestora", "gestora", "1234");
    Funcionario& funcionario = ambiente.controller.adicionarFuncionario("Joao Silva", "joao", "abcd");
    ambiente.controller.adicionarProduto("Termometro", "Equipamento", 12.50, 10);
    Medicamento& medicamento = ambiente.controller.adicionarMedicamento(
        "Antibiotico", "Medicamento", 8.0, 5, true);

    ambiente.controller.autenticar("joao", "abcd");
    Venda& venda = ambiente.controller.registarVenda(
        {{1, 2}, {2, 1}},
        Data(19, 5, 2026),
        "Ana Paciente",
        true);

    confirmar(venda.getFuncionario() == &funcionario, "Venda deve guardar funcionario autenticado.");
    confirmarIgual(33.0, venda.getTotal(), "Venda deve calcular total.");
    confirmar(venda.getCliente() != nullptr, "Venda deve guardar cliente.");
    confirmar(venda.getNomePaciente() == "Ana Paciente", "Venda deve guardar nome do cliente.");
    confirmar(venda.getReceita() != nullptr, "Venda com medicamento sujeito a receita deve criar receita.");
    confirmar(venda.getReceita()->getCliente() == venda.getCliente(),
              "Receita deve ficar associada ao cliente da venda.");
    confirmar(venda.getReceita()->getMedicamento() == medicamento.getNome(),
              "Receita deve referir o medicamento vendido.");
    confirmar(venda.getReceita()->foiUtilizada(), "Receita criada na venda deve ficar utilizada.");
    confirmar(ambiente.controller.consultarStock(1) == 8, "Venda deve reduzir stock do produto.");
    confirmar(ambiente.controller.consultarStock(2) == 4, "Venda deve reduzir stock do medicamento.");
    confirmar(ambiente.controller.listarClientes().size() == 1, "Venda deve criar um cliente.");
    confirmar(ambiente.controller.listarReceitas().size() == 1, "Venda deve criar uma receita.");
}

void venda_recusa_medicamento_sem_receita_validada() {
    AmbienteController ambiente;
    ambiente.controller.adicionarFuncionario("Joao Silva", "joao", "abcd");
    ambiente.controller.adicionarMedicamento("Antibiotico", "Medicamento", 8.0, 5, true);

    ambiente.controller.autenticar("joao", "abcd");
    confirmarExcecao<std::runtime_error>(
        [&ambiente]() {
            ambiente.controller.registarVenda({{1, 1}}, Data(19, 5, 2026), "Ana Paciente", false);
        },
        "Medicamento sujeito a receita deve exigir receita validada.");
    confirmar(ambiente.controller.listarVendas().empty(), "Venda recusada nao deve ser guardada.");
    confirmar(ambiente.controller.consultarStock(1) == 5, "Venda recusada nao deve alterar stock.");
}

} // namespace

std::vector<TestCase> obterTestesVenda() {
    return {
        {"Venda: cria cliente receita e atualiza stock",
         venda_com_receita_cria_cliente_receita_e_atualiza_stock},
        {"Venda: recusa medicamento sem receita validada",
         venda_recusa_medicamento_sem_receita_validada},
    };
}
