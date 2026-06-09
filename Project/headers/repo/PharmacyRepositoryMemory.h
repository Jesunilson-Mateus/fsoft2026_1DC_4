#ifndef FSOFT2026_1DC_4_PHARMACYREPOSITORYMEMORY_H
#define FSOFT2026_1DC_4_PHARMACYREPOSITORYMEMORY_H

#include "IPharmacyRepository.h"

class PharmacyRepositoryMemory : public IPharmacyRepository {
private:
    std::vector<std::unique_ptr<Produto>> produtos;
    std::vector<std::unique_ptr<Funcionario>> funcionarios;
    std::vector<std::unique_ptr<Receita>> receitas;
    std::vector<std::unique_ptr<Venda>> vendas;

public:
    std::vector<std::unique_ptr<Produto>>& getProdutos() override;
    std::vector<std::unique_ptr<Funcionario>>& getFuncionarios() override;
    std::vector<std::unique_ptr<Receita>>& getReceitas() override;
    std::vector<std::unique_ptr<Venda>>& getVendas() override;
};

#endif //FSOFT2026_1DC_4_PHARMACYREPOSITORYMEMORY_H
