#include "TestUtils.h"

namespace {

void relatorio_resume_vendas() {
    AmbienteController ambiente;
    ambiente.controller.adicionarGestor("Maria Gestora", "gestora", "1234");
    ambiente.controller.adicionarFuncionario("Joao Silva", "joao", "abcd");
    ambiente.controller.adicionarProduto("Termometro", "Equipamento", 12.50, 10);
    ambiente.controller.adicionarProduto("Seringa", "Equipamento", 1.25, 20);

    ambiente.controller.autenticar("joao", "abcd");
    ambiente.controller.registarVenda({{1, 2}, {2, 4}}, Data(19, 5, 2026), "Ana Paciente");

    ambiente.controller.autenticar("gestora", "1234");
    RelatorioResumo resumo = ambiente.controller.gerarRelatorioResumo();

    confirmar(resumo.totalProdutos == 2, "Relatorio deve contar produtos.");
    confirmar(resumo.totalVendas == 1, "Relatorio deve contar vendas.");
    confirmar(resumo.totalItensVendidos == 6, "Relatorio deve somar itens vendidos.");
    confirmarIgual(30.0, resumo.totalFaturado, "Relatorio deve somar faturacao.");
}

} // namespace

std::vector<TestCase> obterTestesRelatorio() {
    return {
        {"Relatorio: resume vendas", relatorio_resume_vendas},
    };
}
