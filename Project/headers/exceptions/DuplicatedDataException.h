#ifndef FSOFT2026_1DC_4_DUPLICATEDDATAEXCEPTION_H
#define FSOFT2026_1DC_4_DUPLICATEDDATAEXCEPTION_H

#include <exception>
#include <string>

class DuplicatedDataException : public std::exception {
private:
    std::string mensagem;

public:
    explicit DuplicatedDataException(const std::string& msg) : mensagem(msg) {}

    const char* what() const noexcept override {
        return mensagem.c_str();
    }
};

#endif //FSOFT2026_1DC_4_DUPLICATEDDATAEXCEPTION_H
