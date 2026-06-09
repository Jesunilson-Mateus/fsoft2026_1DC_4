#ifndef FSOFT2026_1DC_4_IREPOSITORIOFARMACIA_H
#define FSOFT2026_1DC_4_IREPOSITORIOFARMACIA_H

#include "../model/Entidades/Funcionario.h"
#include "../model/Entidades/Produto.h"
#include "../model/Entidades/Receita.h"
#include "../model/Entidades/Venda.h"
#include <memory>
#include <vector>

class IRepositorioFarmacia {
public:
    virtual std::vector<std::unique_ptr<Produto>>& getProdutos() = 0;
    virtual std::vector<std::unique_ptr<Funcionario>>& getFuncionarios() = 0;
    virtual std::vector<std::unique_ptr<Receita>>& getReceitas() = 0;
    virtual std::vector<std::unique_ptr<Venda>>& getVendas() = 0;
    virtual ~IRepositorioFarmacia() = default;
};

#endif //FSOFT2026_1DC_4_IREPOSITORIOFARMACIA_H
