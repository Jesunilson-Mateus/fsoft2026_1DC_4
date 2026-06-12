#ifndef FSOFT2026_1DC_4_STOCKVIEW_H
#define FSOFT2026_1DC_4_STOCKVIEW_H

#include "../controllers/Controller.h"
#include <string>

class StockView {
public:
    static void gerirStock(Controller& controller, const std::string& ficheiroStock);
};

#endif //FSOFT2026_1DC_4_STOCKVIEW_H
