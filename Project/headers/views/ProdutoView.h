#ifndef FSOFT2026_1DC_4_PRODUTOVIEW_H
#define FSOFT2026_1DC_4_PRODUTOVIEW_H

#include "../controllers/Controller.h"

class ProdutoView {
public:
    static void listarProdutos(const Controller& controller);
    static void adicionarProduto(Controller& controller);
};

#endif //FSOFT2026_1DC_4_PRODUTOVIEW_H
