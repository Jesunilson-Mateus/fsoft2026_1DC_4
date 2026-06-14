#include "TestUtils.h"

TEST(ControllerTest, ControlaPermissoesDeStock) {
    AmbienteController ambiente;
    Gestor& gestor = ambiente.controller.adicionarGestor("Maria Gestora", "gestora", "1234");
    Funcionario& funcionario = ambiente.controller.adicionarFuncionario("Joao Silva", "joao", "abcd");
    ambiente.controller.adicionarProduto("Termometro", "Equipamento", 12.50, 10);

    EXPECT_EQ(&funcionario, ambiente.controller.autenticar("joao", "abcd"));
    EXPECT_EQ(10, ambiente.controller.consultarStock(1));
    EXPECT_THROW(ambiente.controller.adicionarStock(1, 3), std::runtime_error);

    EXPECT_EQ(&gestor, ambiente.controller.autenticar("gestora", "1234"));
    ambiente.controller.adicionarStock(1, 5);
    EXPECT_EQ(15, ambiente.controller.consultarStock(1));
}

TEST(ControllerTest, RemoveFuncionarioComRegrasDeGestor) {
    AmbienteController ambiente;
    ambiente.controller.adicionarGestor("Maria Gestora", "gestora", "1234");
    ambiente.controller.adicionarFuncionario("Joao Silva", "joao", "abcd");
    ambiente.controller.adicionarFuncionario("Carlos Temporario", "carlos", "temp");

    ambiente.controller.autenticar("gestora", "1234");
    EXPECT_EQ(3, ambiente.controller.listarFuncionarios().size());

    ambiente.controller.removerFuncionario(3);
    EXPECT_EQ(2, ambiente.controller.listarFuncionarios().size());
    EXPECT_EQ(nullptr, ambiente.controller.autenticar("carlos", "temp"));

    ambiente.controller.autenticar("gestora", "1234");
    EXPECT_THROW(ambiente.controller.removerFuncionario(1), std::runtime_error);
}
