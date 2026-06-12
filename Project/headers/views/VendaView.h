#ifndef FSOFT2026_1DC_4_VENDAVIEW_H
#define FSOFT2026_1DC_4_VENDAVIEW_H

#include "../controllers/Controller.h"
#include <string>

class VendaView {
public:
    static void registarVenda(Controller& controller, const std::string& ficheiroStock);
    static void listarReceitas(const Controller& controller);
};

#endif //FSOFT2026_1DC_4_VENDAVIEW_H
