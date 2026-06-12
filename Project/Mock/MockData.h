#ifndef FSOFT2026_1DC_4_MOCKDATA_H
#define FSOFT2026_1DC_4_MOCKDATA_H

#include "../headers/controllers/Controller.h"

class MockData {
private:
    static void inserirClientes(Controller& controller);
    static void inserirFuncionarios(Controller& controller);
    static void inserirProdutos(Controller& controller);

public:
    static void carregarDadosIniciais(Controller& controller);
};

#endif //FSOFT2026_1DC_4_MOCKDATA_H
