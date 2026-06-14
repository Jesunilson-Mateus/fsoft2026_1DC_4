#include "TestUtils.h"

TEST(FuncionarioTest, Autenticacao) {
    Funcionario funcionario("Joao Silva", "joao", "abcd", "Funcionario");

    EXPECT_TRUE(funcionario.autenticar("joao", "abcd"));
    EXPECT_FALSE(funcionario.autenticar("joao", "errada"));
    EXPECT_TRUE(funcionario == "joao");

    EXPECT_THROW(Funcionario invalido("Jo", "joao", "abcd", "Funcionario"), std::invalid_argument);
    EXPECT_THROW(Funcionario invalido("Joao Silva", "js", "abcd", "Funcionario"), std::invalid_argument);
}
