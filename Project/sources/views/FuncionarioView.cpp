#include "../../headers/views/FuncionarioView.h"
#include "../../headers/exceptions/DuplicatedDataException.h"
#include "../../headers/exceptions/InvalidDataException.h"
#include "../../headers/views/Utils.h"
#include <iomanip>
#include <iostream>

void FuncionarioView::listarFuncionarios(const Controller& controller) {
    std::cout << "\nFuncionarios registados\n";
    std::cout << std::left << std::setw(8) << "Opcao" << std::setw(24) << "Nome"
              << std::setw(18) << "Username" << "Cargo\n";

    int opcao = 1;
    for (const auto& funcionario : controller.listarFuncionarios()) {
        std::cout << std::left << std::setw(8) << opcao++
                  << std::setw(24) << funcionario->getNome()
                  << std::setw(18) << funcionario->getUsername()
                  << funcionario->getCargo()
                  << "\n";
    }
}

void FuncionarioView::gerirFuncionarios(Controller& controller) {
    std::cout << "1 - Adicionar funcionario/gestor\n";
    std::cout << "2 - Listar funcionarios\n";
    std::cout << "3 - Eliminar funcionario/gestor\n";
    int opcao{};
    if (!Utils::lerInteiroOpcional("Opcao", opcao)) {
        std::cout << "Operacao cancelada.\n";
        return;
    }

    if (opcao == 1) {
        adicionarFuncionario(controller);
    } else if (opcao == 2) {
        listarFuncionarios(controller);
    } else if (opcao == 3) {
        removerFuncionario(controller);
    } else {
        throw InvalidDataException("Opcao invalida");
    }
}

void FuncionarioView::removerFuncionario(Controller& controller) {
    listarFuncionarios(controller);

    int posicaoFuncionario{};
    if (!Utils::lerInteiroOpcional("Opcao do funcionario a eliminar", posicaoFuncionario)) {
        std::cout << "Eliminacao cancelada.\n";
        return;
    }

    if (!Utils::lerSimNao("Confirmar eliminacao do funcionario")) {
        std::cout << "Eliminacao cancelada.\n";
        return;
    }

    controller.removerFuncionario(posicaoFuncionario);
    std::cout << "Funcionario eliminado com sucesso.\n";
}

void FuncionarioView::adicionarFuncionario(Controller& controller) {
    std::string nome;
    std::string username;
    std::string password;

    if (!Utils::lerTextoOpcional("Nome", nome)) {
        std::cout << "Adicao cancelada.\n";
        return;
    }
    if (nome.empty() || nome.length() < 3) {
        throw InvalidDataException("Nome deve ter pelo menos 3 caracteres");
    }

    if (!Utils::lerTextoOpcional("Username", username)) {
        std::cout << "Adicao cancelada.\n";
        return;
    }
    if (username.empty() || username.length() < 3) {
        throw InvalidDataException("Username deve ter pelo menos 3 caracteres");
    }

    for (const auto& func : controller.listarFuncionarios()) {
        if (func->getUsername() == username) {
            throw DuplicatedDataException("Username ja existe no sistema");
        }
    }

    if (!Utils::lerTextoOpcional("Password", password)) {
        std::cout << "Adicao cancelada.\n";
        return;
    }
    if (password.empty() || password.length() < 4) {
        throw InvalidDataException("Password deve ter pelo menos 4 caracteres");
    }

    std::cout << "1 - Funcionario\n";
    std::cout << "2 - Gestor\n";
    int tipo{};
    if (!Utils::lerInteiroOpcional("Tipo", tipo)) {
        std::cout << "Adicao cancelada.\n";
        return;
    }

    if (tipo == 1) {
        controller.adicionarFuncionario(nome, username, password);
    } else if (tipo == 2) {
        controller.adicionarGestor(nome, username, password);
    } else {
        throw InvalidDataException("Tipo de utilizador invalido");
    }

    std::cout << "Utilizador criado com sucesso.\n";
}
