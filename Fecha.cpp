#include "Fecha.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

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

void Fecha::sumarDias(int dias) {
    std::tm tiempo = {};
    tiempo.tm_mday = _dia;
    tiempo.tm_mon = _mes - 1; // tm_mon va de 0 a 11
    tiempo.tm_year = _anio - 1900; // tm_year = año desde 1900

    std::time_t tiempo_epoch = std::mktime(&tiempo);
    tiempo_epoch += dias * 86400; // 86400 segundos por día

    std::tm* nuevaFecha = std::localtime(&tiempo_epoch);
    _dia = nuevaFecha->tm_mday;
    _mes = nuevaFecha->tm_mon + 1;
    _anio = nuevaFecha->tm_year + 1900;
}

bool Fecha::operator==(const Fecha& otra) const {
    return _dia == otra._dia && _mes == otra._mes && _anio == otra._anio;
}

std::string Fecha::toString() const {
    std::string diaStr = (_dia < 10 ? "0" : "") + std::to_string(_dia);
    std::string mesStr = (_mes < 10 ? "0" : "") + std::to_string(_mes);
    std::string anioStr = std::to_string(_anio);
    return diaStr + "/" + mesStr + "/" + anioStr;
}
