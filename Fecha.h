#pragma once
#include <string>

using namespace std;

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
    void sumarDias(int dias);
    bool operator==(const Fecha& otra) const;
    std::string toString();
    static bool esFechaNacimientoValida(int dia, int mes, int anio);
    bool esFechaTurnoValida();
    static Fecha leerFechaValida(std::string mensaje = "Ingrese la fecha (dd/mm/aaaa): ",bool validarNacimiento = false,bool validarTurno = false);
    static Fecha leerMesAnioValido(std::string mensaje = "Ingrese el mes y anio (MM/AAAA): ");


};


