#ifndef FSOFT2026_1DC_4_UTILS_H
#define FSOFT2026_1DC_4_UTILS_H

#include "../model/Entidades/Data.h"
#include <string>

class Utils {
public:
    static void limparEntrada();
    static int lerInteiro(const std::string& mensagem);
    static bool lerInteiroOpcional(const std::string& mensagem, int& valor);
    static bool lerDoubleOpcional(const std::string& mensagem, double& valor);
    static std::string lerTexto(const std::string& mensagem);
    static bool lerTextoOpcional(const std::string& mensagem, std::string& valor);
    static bool lerSimNao(const std::string& mensagem);
    static bool pediuVoltar(const std::string& valor);
};

#endif //FSOFT2026_1DC_4_UTILS_H
