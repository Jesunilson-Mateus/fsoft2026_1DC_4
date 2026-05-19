//
// Data.h - Gestão de datas
// Criado para o Sistema de Gestão de Farmácia
//

#ifndef PROJECT_HEADERS_MODEL_ENTIDADES_DATA_H_
#define PROJECT_HEADERS_MODEL_ENTIDADES_DATA_H_

class Data {
private:
    int dia{};
    int mes{}; // 1-janeiro, ... 12-dezembro
    int ano{};

    static bool ehAnoBissexto(int ano);
    static bool ehValida(int dia, int mes, int ano);
    
public:
    Data();
    Data(int dia, int mes, int ano);
    Data(const Data& data);
    
    void definirData(int dia, int mes, int ano);
    void obterData(int& dia, int& mes, int& ano) const;
    
    bool operator==(const Data& outra) const;
    bool operator>(const Data& outra) const;
    bool operator<(const Data& outra) const;
    
    ~Data() = default;
};

#endif // PROJECT_HEADERS_MODEL_ENTIDADES_DATA_H_
