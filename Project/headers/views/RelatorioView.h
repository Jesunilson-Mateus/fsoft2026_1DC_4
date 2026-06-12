#ifndef FSOFT2026_1DC_4_RELATORIOVIEW_H
#define FSOFT2026_1DC_4_RELATORIOVIEW_H

#include "../controllers/Controller.h"

class RelatorioView {
private:
    static void mostrarRelatorio(Controller& controller);

public:
    static void gerirRelatorios(Controller& controller);
};

#endif //FSOFT2026_1DC_4_RELATORIOVIEW_H
