#include "Fecha.h"
#include <cstring>
#include <iostream>

Fecha::Fecha() {
    _dia = 1;
    _mes = 1;
    _anio = 1900;
}

Fecha::Fecha(int dia, int mes, int anio) {
    _dia = dia;
    _mes = mes;
    _anio = anio;
}

void Fecha::setDia(int dia) {
    _dia = dia;
}

void Fecha::setMes(int mes) {
    _mes = mes;
}

void Fecha::setAnio(int anio) {
    _anio = anio;
}

int Fecha::getDia() const {
    return _dia;
}

int Fecha::getMes() const {
    return _mes;
}

int Fecha::getAnio() const {
    return _anio;
}

bool Fecha::esValida(int dia, int mes, int anio) {
    if (anio < 1 || mes < 1 || mes > 12 || dia < 1) return false;

    int diasEnMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool bisiesto = (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0));

    if (bisiesto && mes == 2) return dia <= 29;

    return dia <= diasEnMes[mes - 1];
}

std::string Fecha::toString() const {
    std::string diaStr = (_dia < 10 ? "0" : "") + std::to_string(_dia);
    std::string mesStr = (_mes < 10 ? "0" : "") + std::to_string(_mes);
    std::string anioStr = std::to_string(_anio);
    return diaStr + "/" + mesStr + "/" + anioStr;
}
