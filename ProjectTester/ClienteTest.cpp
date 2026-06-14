#include "TestUtils.h"

namespace {

void cliente_valida_nif_e_igualdade() {
    Cliente cliente("Ana Paciente", "123456789", "912345678");
    Cliente mesmoNif("Outro Nome", "123456789");
    Cliente mesmoNome("Ana Paciente");

    confirmar(cliente.getNif() == "123456789", "Cliente deve guardar NIF valido.");
    confirmar(cliente == mesmoNif, "Clientes com o mesmo NIF devem ser iguais.");
    confirmar(cliente == mesmoNome, "Cliente com NIF pode ser igual por nome quando o outro nao tem NIF.");

    confirmarExcecao<std::invalid_argument>(
        []() { Cliente invalido("An", "123456789"); },
        "Cliente com nome curto deve ser rejeitado.");
    confirmarExcecao<std::invalid_argument>(
        []() { Cliente invalido("Ana Paciente", "123"); },
        "Cliente com NIF invalido deve ser rejeitado.");
}

} // namespace

std::vector<TestCase> obterTestesCliente() {
    return {
        {"Cliente: valida NIF e igualdade", cliente_valida_nif_e_igualdade},
    };
}
