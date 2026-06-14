#include "TestUtils.h"

namespace {

void produto_valida_dados_e_stock() {
    Produto produto("Termometro", "Equipamento", 12.50, 10);

    confirmar(produto.getNome() == "Termometro", "Produto deve guardar o nome.");
    confirmar(produto.verificarDisponibilidade(10), "Produto deve ter stock disponivel.");
    confirmar(!produto.verificarDisponibilidade(11), "Produto nao deve vender acima do stock.");

    produto.adicionarStock(5);
    confirmar(produto.getQuantidadeStock() == 15, "Adicionar stock deve aumentar quantidade.");

    produto.removerStock(4);
    confirmar(produto.getQuantidadeStock() == 11, "Remover stock deve reduzir quantidade.");

    confirmarExcecao<std::invalid_argument>(
        []() { Produto invalido("AB", "Equipamento", 12.50, 10); },
        "Produto com nome curto deve ser rejeitado.");
    confirmarExcecao<std::invalid_argument>(
        [&produto]() { produto.removerStock(12); },
        "Remover mais stock do que existe deve falhar.");
}

} // namespace

std::vector<TestCase> obterTestesProduto() {
    return {
        {"Produto: valida dados e stock", produto_valida_dados_e_stock},
    };
}
