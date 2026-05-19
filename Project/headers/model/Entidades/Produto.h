#ifndef PROJECT_HEADERS_MODEL_ENTIDADES_PRODUTO_H_
#define PROJECT_HEADERS_MODEL_ENTIDADES_PRODUTO_H_

#include <string>

class Produto {
protected:
    static int proximoId;
    int id{};
    std::string nome;
    std::string categoria;
    double preco{};
    int quantidadeStock{};
    std::string descricao;

    static bool ehNomeValido(const std::string& nome);
    static bool ehPrecoValido(double preco);
    static bool ehQuantidadeValida(int quantidade);

public:
    Produto();
    Produto(const std::string& nome, const std::string& categoria,
            double preco, int quantidadeStock, const std::string& descricao = "");
    virtual ~Produto() = default;

    int getId() const;
    const std::string& getNome() const;
    const std::string& getCategoria() const;
    double getPreco() const;
    int getQuantidadeStock() const;
    const std::string& getDescricao() const;

    void setNome(const std::string& nome);
    void setCategoria(const std::string& categoria);
    void setPreco(double preco);
    void setDescricao(const std::string& descricao);

    bool verificarDisponibilidade(int quantidade = 1) const;
    void atualizarStock(int quantidade);
    void adicionarStock(int quantidade);
    void removerStock(int quantidade);

    bool operator==(const Produto& outro) const;
    bool operator==(int id) const;
};

#endif // PROJECT_HEADERS_MODEL_ENTIDADES_PRODUTO_H_
