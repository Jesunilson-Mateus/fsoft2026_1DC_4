#include "TestUtils.h"

namespace {

void funcionario_autenticacao() {
    Funcionario funcionario("Joao Silva", "joao", "abcd", "Funcionario");

    confirmar(funcionario.autenticar("joao", "abcd"), "Credenciais certas devem autenticar.");
    confirmar(!funcionario.autenticar("joao", "errada"), "Password errada nao deve autenticar.");
    confirmar(funcionario == "joao", "Operador de igualdade deve comparar username.");

    confirmarExcecao<std::invalid_argument>(
        []() { Funcionario invalido("Jo", "joao", "abcd", "Funcionario"); },
        "Funcionario com nome curto deve ser rejeitado.");
    confirmarExcecao<std::invalid_argument>(
        []() { Funcionario invalido("Joao Silva", "js", "abcd", "Funcionario"); },
        "Funcionario com username curto deve ser rejeitado.");
}

} // namespace

std::vector<TestCase> obterTestesFuncionario() {
    return {
        {"Funcionario: autenticacao", funcionario_autenticacao},
    };
}
