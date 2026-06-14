#include "TestUtils.h"

TEST(VendaTest, CriaClienteReceitaEAtualizaStock) {
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

    EXPECT_EQ(&funcionario, venda.getFuncionario());
    EXPECT_DOUBLE_EQ(33.0, venda.getTotal());
    ASSERT_NE(nullptr, venda.getCliente());
    EXPECT_EQ("Ana Paciente", venda.getNomePaciente());
    ASSERT_NE(nullptr, venda.getReceita());
    EXPECT_EQ(venda.getCliente(), venda.getReceita()->getCliente());
    EXPECT_EQ(medicamento.getNome(), venda.getReceita()->getMedicamento());
    EXPECT_TRUE(venda.getReceita()->foiUtilizada());
    EXPECT_EQ(8, ambiente.controller.consultarStock(1));
    EXPECT_EQ(4, ambiente.controller.consultarStock(2));
    EXPECT_EQ(1, ambiente.controller.listarClientes().size());
    EXPECT_EQ(1, ambiente.controller.listarReceitas().size());
}

TEST(VendaTest, RecusaMedicamentoSemReceitaValidada) {
    AmbienteController ambiente;
    ambiente.controller.adicionarFuncionario("Joao Silva", "joao", "abcd");
    ambiente.controller.adicionarMedicamento("Antibiotico", "Medicamento", 8.0, 5, true);

    ambiente.controller.autenticar("joao", "abcd");
    EXPECT_THROW(
        ambiente.controller.registarVenda({{1, 1}}, Data(19, 5, 2026), "Ana Paciente", false),
        std::runtime_error);
    EXPECT_TRUE(ambiente.controller.listarVendas().empty());
    EXPECT_EQ(5, ambiente.controller.consultarStock(1));
}
