#include "TestUtils.h"

TEST(ProdutoTest, ValidaDadosEStock) {
    Produto produto("Termometro", "Equipamento", 12.50, 10);

    EXPECT_EQ("Termometro", produto.getNome());
    EXPECT_TRUE(produto.verificarDisponibilidade(10));
    EXPECT_FALSE(produto.verificarDisponibilidade(11));

    produto.adicionarStock(5);
    EXPECT_EQ(15, produto.getQuantidadeStock());

    produto.removerStock(4);
    EXPECT_EQ(11, produto.getQuantidadeStock());

    EXPECT_THROW(Produto invalido("AB", "Equipamento", 12.50, 10), std::invalid_argument);
    EXPECT_THROW(produto.removerStock(12), std::invalid_argument);
}
