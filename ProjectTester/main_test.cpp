#include "TestUtils.h"
#include <iostream>
#include <vector>

namespace {

void adicionarTestes(std::vector<TestCase>& destino, const std::vector<TestCase>& origem) {
    destino.insert(destino.end(), origem.begin(), origem.end());
}

} // namespace

int main() {
    std::vector<TestCase> testes;
    adicionarTestes(testes, obterTestesProduto());
    adicionarTestes(testes, obterTestesCliente());
    adicionarTestes(testes, obterTestesFuncionario());
    adicionarTestes(testes, obterTestesController());
    adicionarTestes(testes, obterTestesVenda());
    adicionarTestes(testes, obterTestesRelatorio());

    int falhas = 0;
    for (const auto& teste : testes) {
        try {
            teste.executar();
            std::cout << "[OK] " << teste.nome << "\n";
        } catch (const std::exception& erro) {
            ++falhas;
            std::cerr << "[FALHOU] " << teste.nome << ": " << erro.what() << "\n";
        }
    }

    if (falhas > 0) {
        std::cerr << falhas << " teste(s) falharam.\n";
        return 1;
    }

    std::cout << "Todos os testes unitarios passaram com sucesso.\n";
    return 0;
}
