//
// Data.cpp - Implementação de Data
//

#include "../../headers/model/Entidades/Data.h"
#include <stdexcept>
#include <string>

using namespace std;

bool Data::ehAnoBissexto(const int ano) {
    if (ano % 400 == 0) return true;
    if (ano % 100 == 0) return false;
    if (ano % 4 == 0) return true;
    return false;
}

bool Data::ehValida(const int dia, const int mes, const int ano) {
    if (dia <= 0 || dia > 31 || mes <= 0 || mes > 12) {
        return false;
    }

    switch (mes) {
        case 2:
            if (ehAnoBissexto(ano)) {
                return dia <= 29;
            } else {
                return dia <= 28;
            }
        case 4:
        case 6:
        case 9:
        case 11:
            return dia <= 30;
        default:
            return true;
    }
}

Data::Data() : dia(1), mes(1), ano(1900) {}

Data::Data(const int dia, const int mes, const int ano) {
    definirData(dia, mes, ano);
}

Data::Data(const Data& data) {
    definirData(data.dia, data.mes, data.ano);
}

void Data::definirData(const int dia, const int mes, const int ano) {
    if (ehValida(dia, mes, ano)) {
        this->dia = dia;
        this->mes = mes;
        this->ano = ano;
    } else {
        throw invalid_argument("Data inválida: " + to_string(dia) + "/" + to_string(mes) + "/" + to_string(ano));
    }
}

void Data::obterData(int& dia, int& mes, int& ano) const {
    dia = this->dia;
    mes = this->mes;
    ano = this->ano;
}

bool Data::operator==(const Data& outra) const {
    return (this->dia == outra.dia && this->mes == outra.mes && this->ano == outra.ano);
}

bool Data::operator>(const Data& outra) const {
    if (this->ano > outra.ano) return true;
    if (this->ano == outra.ano && this->mes > outra.mes) return true;
    if (this->ano == outra.ano && this->mes == outra.mes && this->dia > outra.dia) return true;
    return false;
}

bool Data::operator<(const Data& outra) const {
    if (*this == outra) return false;
    if (*this > outra) return false;
    return true;
}
