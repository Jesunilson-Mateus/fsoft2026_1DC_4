#ifndef FSOFT2026_1DC_4_DATACONSISTENCYEXCEPTION_H
#define FSOFT2026_1DC_4_DATACONSISTENCYEXCEPTION_H

#include <exception>
#include <string>

class DataConsistencyException : public std::exception {
private:
    std::string mensagem;

public:
    explicit DataConsistencyException(const std::string& msg) : mensagem(msg) {}

    const char* what() const noexcept override {
        return mensagem.c_str();
    }
};

#endif //FSOFT2026_1DC_4_DATACONSISTENCYEXCEPTION_H
