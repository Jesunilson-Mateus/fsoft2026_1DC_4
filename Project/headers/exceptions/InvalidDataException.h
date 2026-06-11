#ifndef FSOFT2026_1DC_4_INVALIDDATAEXCEPTION_H
#define FSOFT2026_1DC_4_INVALIDDATAEXCEPTION_H

#include <exception>
#include <string>

class InvalidDataException : public std::exception {
private:
    std::string mensagem;

public:
    explicit InvalidDataException(const std::string& msg) : mensagem(msg) {}

    const char* what() const noexcept override {
        return mensagem.c_str();
    }
};

#endif //FSOFT2026_1DC_4_INVALIDDATAEXCEPTION_H
