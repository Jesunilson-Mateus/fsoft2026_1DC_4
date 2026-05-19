#include "Data.h"
#include <stdexcept>
#include <string>

bool Data::ehAnoBissexto(int ano) {
    if (ano % 400 == 0) return true;
    if (ano % 100 == 0) return false;
    return ano % 4 == 0;
}

bool Data::ehValida(int dia, int mes, int ano) {
    if (ano < 1900 || dia < 1 || mes < 1 || mes > 12) return false;

    int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mes == 2 && ehAnoBissexto(ano)) return dia <= 29;
    return dia <= diasNoMes[mes - 1];
}

Data::Data() : dia(1), mes(1), ano(1900) {}

Data::Data(int dia, int mes, int ano) {
    definirData(dia, mes, ano);
}

void Data::definirData(int dia, int mes, int ano) {
    if (!ehValida(dia, mes, ano)) {
        throw std::invalid_argument("Data invalida: " + std::to_string(dia) + "/" +
                                    std::to_string(mes) + "/" + std::to_string(ano));
    }

    this->dia = dia;
    this->mes = mes;
    this->ano = ano;
}

void Data::obterData(int& dia, int& mes, int& ano) const {
    dia = this->dia;
    mes = this->mes;
    ano = this->ano;
}

bool Data::operator==(const Data& outra) const {
    return dia == outra.dia && mes == outra.mes && ano == outra.ano;
}

bool Data::operator>(const Data& outra) const {
    if (ano != outra.ano) return ano > outra.ano;
    if (mes != outra.mes) return mes > outra.mes;
    return dia > outra.dia;
}

bool Data::operator<(const Data& outra) const {
    return !(*this == outra) && !(*this > outra);
}

