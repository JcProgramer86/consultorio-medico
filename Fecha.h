#pragma once
#include <string>


class Fecha {
private:
    int _dia;
    int _mes;
    int _anio;

public:

    Fecha();
    Fecha(int dia, int mes, int anio);


    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);


    int getDia() const;
    int getMes() const;
    int getAnio() const;


    static bool esValida(int dia, int mes, int anio);
    std::string toString() const;
};

