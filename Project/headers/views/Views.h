#ifndef FSOFT2026_1DC_4_VIEWS_H
#define FSOFT2026_1DC_4_VIEWS_H

#include "../controllers/Controller.h"
#include <string>

class Views {
private:
    static void iniciarSessao(Controller& controller);
    static void mostrarMenu(const Controller& controller, const std::string& nomeFarmacia);

public:
    static void executar(Controller& controller, const std::string& ficheiroStock);
};

#endif //FSOFT2026_1DC_4_VIEWS_H
