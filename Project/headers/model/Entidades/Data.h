#ifndef PROJECT_HEADERS_MODEL_ENTIDADES_DATA_H_
#define PROJECT_HEADERS_MODEL_ENTIDADES_DATA_H_

class Data {
private:
    int dia{};
    int mes{};
    int ano{};

    static bool ehAnoBissexto(int ano);
    static bool ehValida(int dia, int mes, int ano);

public:
    Data();
    Data(int dia, int mes, int ano);

    void definirData(int dia, int mes, int ano);
    void obterData(int& dia, int& mes, int& ano) const;

    bool operator==(const Data& outra) const;
    bool operator>(const Data& outra) const;
    bool operator<(const Data& outra) const;
};

#endif // PROJECT_HEADERS_MODEL_ENTIDADES_DATA_H_
