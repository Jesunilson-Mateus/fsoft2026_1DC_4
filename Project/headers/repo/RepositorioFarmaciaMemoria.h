#ifndef FSOFT2026_1DC_4_REPOSITORIOFARMACIAMEMORIA_H
#define FSOFT2026_1DC_4_REPOSITORIOFARMACIAMEMORIA_H

#include "IRepositorioFarmacia.h"
#include <string>

class RepositorioFarmaciaMemoria : public IRepositorioFarmacia {
private:
    std::vector<std::unique_ptr<Cliente>> clientes;
    std::vector<std::unique_ptr<Produto>> produtos;
    std::vector<std::unique_ptr<Funcionario>> funcionarios;
    std::vector<std::unique_ptr<Receita>> receitas;
    std::vector<std::unique_ptr<Venda>> vendas;

public:
    std::vector<std::unique_ptr<Cliente>>& getClientes() override;
    std::vector<std::unique_ptr<Produto>>& getProdutos() override;
    std::vector<std::unique_ptr<Funcionario>>& getFuncionarios() override;
    std::vector<std::unique_ptr<Receita>>& getReceitas() override;
    std::vector<std::unique_ptr<Venda>>& getVendas() override;
    Funcionario& guardarFuncionario(std::unique_ptr<Funcionario> funcionario) override;
    void removerFuncionarioPorPosicao(int posicaoFuncionario) override;

    void carregarStockGuardado(const std::string& caminhoFicheiro) override;
    void guardarStock(const std::string& caminhoFicheiro) const override;
};

#endif //FSOFT2026_1DC_4_REPOSITORIOFARMACIAMEMORIA_H
