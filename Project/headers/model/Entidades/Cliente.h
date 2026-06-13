#ifndef PROJECT_HEADERS_MODEL_ENTIDADES_CLIENTE_H_
#define PROJECT_HEADERS_MODEL_ENTIDADES_CLIENTE_H_

#include <string>

class Cliente {
private:
    std::string nome;
    std::string nif;
    std::string telefone;

    static bool ehNomeValido(const std::string& nome);
    static bool ehNifValido(const std::string& nif);

public:
    Cliente();
    explicit Cliente(const std::string& nome,
                     const std::string& nif = "",
                     const std::string& telefone = "");

    const std::string& getNome() const;
    const std::string& getNif() const;
    const std::string& getTelefone() const;

    void setNif(const std::string& nif);

    bool operator==(const Cliente& outro) const;
};

#endif // PROJECT_HEADERS_MODEL_ENTIDADES_CLIENTE_H_
