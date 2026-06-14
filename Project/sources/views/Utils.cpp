#include "../../headers/views/Utils.h"
#include <iostream>
#include <limits>
#include <sstream>

namespace {
template <typename T>
bool lerNumeroOpcional(const std::string& mensagem, T& valor) {
    std::string entrada;
    while (true) {
        std::cout << mensagem << " (v para voltar): ";
        getline(std::cin, entrada);
        if (Utils::pediuVoltar(entrada)) return false;

        std::istringstream stream(entrada);
        if (stream >> valor && stream.eof()) return true;
        std::cout << "Valor invalido. Tente novamente.\n";
    }
}
}

void Utils::limparEntrada() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int Utils::lerInteiro(const std::string& mensagem) {
    int valor{};
    while (true) {
        std::cout << mensagem;
        if (std::cin >> valor) {
            limparEntrada();
            return valor;
        }
        std::cout << "Valor invalido. Tente novamente.\n";
        limparEntrada();
    }
}

bool Utils::pediuVoltar(const std::string& valor) {
    return valor == "v" || valor == "V";
}

bool Utils::lerInteiroOpcional(const std::string& mensagem, int& valor) {
    return lerNumeroOpcional(mensagem, valor);
}

bool Utils::lerDoubleOpcional(const std::string& mensagem, double& valor) {
    return lerNumeroOpcional(mensagem, valor);
}

std::string Utils::lerTexto(const std::string& mensagem) {
    std::string valor;
    std::cout << mensagem;
    getline(std::cin, valor);
    return valor;
}

bool Utils::lerTextoOpcional(const std::string& mensagem, std::string& valor) {
    std::cout << mensagem << " (v para voltar): ";
    getline(std::cin, valor);
    return !pediuVoltar(valor);
}

bool Utils::lerSimNao(const std::string& mensagem) {
    std::string resposta;
    while (true) {
        std::cout << mensagem << " (sim/nao): ";
        getline(std::cin, resposta);

        if (resposta == "sim" || resposta == "Sim" || resposta == "s" || resposta == "S") {
            return true;
        }
        if (resposta == "nao" || resposta == "Nao" || resposta == "n" || resposta == "N") {
            return false;
        }

        std::cout << "Resposta invalida. Escreva sim ou nao.\n";
    }
}
