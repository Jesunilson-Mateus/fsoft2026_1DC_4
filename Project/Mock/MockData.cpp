#include "MockData.h"

void MockData::inserirFuncionarios(Controller& controller) {
    controller.adicionarGestor("Maria Gestora", "gestora", "1234");
    controller.adicionarFuncionario("Joao Silva", "joao", "abcd");
}

void MockData::inserirProdutos(Controller& controller) {
    controller.adicionarProduto("Termometro", "Equipamento", 12.50, 10);
    controller.adicionarProduto("Mascara Cirurgica", "Protecao", 0.50, 200);
    controller.adicionarMedicamento("Paracetamol", "Medicamento", 3.75, 40, false);
    controller.adicionarMedicamento("Antibiotico", "Medicamento", 8.00, 5, true);
}

void MockData::carregarDadosIniciais(Controller& controller) {
    inserirFuncionarios(controller);
    inserirProdutos(controller);
}
