#ifndef FSOFT2026_1DC_4_FUNCIONARIOVIEW_H
#define FSOFT2026_1DC_4_FUNCIONARIOVIEW_H

#include "../controllers/Controller.h"

class FuncionarioView {
private:
    static void adicionarFuncionario(Controller& controller);
    static void removerFuncionario(Controller& controller);

public:
    static void listarFuncionarios(const Controller& controller);
    static void gerirFuncionarios(Controller& controller);
};

#endif //FSOFT2026_1DC_4_FUNCIONARIOVIEW_H
