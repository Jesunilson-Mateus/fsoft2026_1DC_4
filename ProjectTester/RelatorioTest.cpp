#include "TestUtils.h"

TEST(RelatorioTest, ResumeVendas) {
    AmbienteController ambiente;
    ambiente.controller.adicionarGestor("Maria Gestora", "gestora", "1234");
    ambiente.controller.adicionarFuncionario("Joao Silva", "joao", "abcd");
    ambiente.controller.adicionarProduto("Termometro", "Equipamento", 12.50, 10);
    ambiente.controller.adicionarProduto("Seringa", "Equipamento", 1.25, 20);

    ambiente.controller.autenticar("joao", "abcd");
    ambiente.controller.registarVenda({{1, 2}, {2, 4}}, Data(19, 5, 2026), "Ana Paciente");

    ambiente.controller.autenticar("gestora", "1234");
    RelatorioResumo resumo = ambiente.controller.gerarRelatorioResumo();

    EXPECT_EQ(2, resumo.totalProdutos);
    EXPECT_EQ(1, resumo.totalVendas);
    EXPECT_EQ(6, resumo.totalItensVendidos);
    EXPECT_DOUBLE_EQ(30.0, resumo.totalFaturado);
}
