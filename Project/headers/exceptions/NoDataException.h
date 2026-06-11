#ifndef FSOFT2026_1DC_4_NODATAEXCEPTION_H
#define FSOFT2026_1DC_4_NODATAEXCEPTION_H

#include <exception>
#include <string>

class NoDataException : public std::exception {
private:
    std::string mensagem;

public:
    explicit NoDataException(const std::string& msg) : mensagem(msg) {}

    const char* what() const noexcept override {
        return mensagem.c_str();
    }
};

#endif //FSOFT2026_1DC_4_NODATAEXCEPTION_H
