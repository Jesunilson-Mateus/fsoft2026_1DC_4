//
// Funcionario.h - Classe base de utilizadores autenticados
// Criado para o Sistema de Gestão de Farmácia
//

#ifndef PROJECT_HEADERS_MODEL_ENTIDADES_FUNCIONARIO_H_
#define PROJECT_HEADERS_MODEL_ENTIDADES_FUNCIONARIO_H_

#include <string>

class Funcionario {
protected:
    static int proximoId;
    int id{};
    std::string nome;
    std::string username;
    std::string password;
    std::string cargo; // "Funcionário" ou "Gestor"

    static bool ehNomeValido(const std::string& nome);
    static bool ehUsernameValido(const std::string& username);

public:
    Funcionario();
    Funcionario(const std::string& nome, const std::string& username, 
                const std::string& password, const std::string& cargo);
    virtual ~Funcionario() = default;

    // Getters
    int getId() const;
    const std::string& getNome() const;
    const std::string& getUsername() const;
    const std::string& getPassword() const;
    const std::string& getCargo() const;

    // Setters
    void setNome(const std::string& nome);
    void setPassword(const std::string& password);

    // Autenticação
    bool autenticar(const std::string& username, const std::string& password) const;

    // Comparadores
    bool operator==(const Funcionario& outro) const;
    bool operator==(int id) const;
    bool operator==(const std::string& username) const;
};

#endif // PROJECT_HEADERS_MODEL_ENTIDADES_FUNCIONARIO_H_
