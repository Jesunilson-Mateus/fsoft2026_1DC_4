#ifndef PROJECTTESTER_TESTUTILS_H
#define PROJECTTESTER_TESTUTILS_H

#include "../Project/headers/controllers/Controller.h"
#include "../Project/headers/repo/RepositorioFarmaciaMemoria.h"
#include <cmath>
#include <functional>
#include <stdexcept>
#include <string>
#include <vector>

struct TestCase {
    std::string nome;
    std::function<void()> executar;
};

struct AmbienteController {
    RepositorioFarmaciaMemoria repositorio;
    Controller controller;

    AmbienteController() : repositorio(), controller(&repositorio) {}
};

inline void confirmar(bool condicao, const std::string& mensagem) {
    if (!condicao) {
        throw std::runtime_error(mensagem);
    }
}

inline void confirmarIgual(double esperado, double obtido, const std::string& mensagem) {
    if (std::fabs(esperado - obtido) > 0.0001) {
        throw std::runtime_error(mensagem);
    }
}

template <typename Excecao, typename Funcao>
void confirmarExcecao(Funcao funcao, const std::string& mensagem) {
    try {
        funcao();
    } catch (const Excecao&) {
        return;
    }
    throw std::runtime_error(mensagem);
}

std::vector<TestCase> obterTestesProduto();
std::vector<TestCase> obterTestesCliente();
std::vector<TestCase> obterTestesFuncionario();
std::vector<TestCase> obterTestesController();
std::vector<TestCase> obterTestesVenda();
std::vector<TestCase> obterTestesRelatorio();

#endif // PROJECTTESTER_TESTUTILS_H
