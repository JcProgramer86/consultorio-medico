#include "Fecha.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <regex>

Fecha::Fecha() {
    time_t t = time(nullptr);
    struct tm* now = localtime(&t);
    _dia = now->tm_mday;
    _mes = now->tm_mon + 1;
    _anio = now->tm_year + 1900;
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

std::string Fecha::toString() {
    std::string diaStr = (_dia < 10 ? "0" : "") + std::to_string(_dia);
    std::string mesStr = (_mes < 10 ? "0" : "") + std::to_string(_mes);
    std::string anioStr = std::to_string(_anio);
    return diaStr + "/" + mesStr + "/" + anioStr;
}

bool Fecha::esFechaNacimientoValida(int dia, int mes, int anio) {
    if (!esValida(dia, mes, anio)) return false;
    Fecha hoy;
    int edad = hoy._anio - anio;
    if (hoy._mes < mes || (hoy._mes == mes && hoy._dia < dia)) {
        edad--;
    }
    if (edad < 0 || edad > 120) return false;
    return true;
}

bool Fecha::esFechaTurnoValida(){
    if (!esValida(_dia, _mes, _anio)) return false;
    Fecha hoy;
    if (*this == hoy) return true;
    if (_anio > hoy._anio) return true;
    if (_anio == hoy._anio && _mes > hoy._mes) return true;
    if (_anio == hoy._anio && _mes == hoy._mes && _dia > hoy._dia) return true;
    return false;
}

Fecha Fecha::leerFechaValida(std::string mensaje, bool validarNacimiento, bool validarTurno) {
    std::string fechaStr;
    int dia, mes, anio;
    std::regex formatoFecha(R"(^\d{1,2}/\d{1,2}/\d{4}$)");

    while (true) {
        std::cout << mensaje;
        std::getline(std::cin, fechaStr);

        if (!std::regex_match(fechaStr, formatoFecha)) {
            std::cout << "[!] Formato incorrecto. Ejemplo válido: 07/09/1990" << std::endl;
            continue;
        }
        std::replace(fechaStr.begin(), fechaStr.end(), '/', ' ');
        std::istringstream iss(fechaStr);
        iss >> dia >> mes >> anio;

        if (!Fecha::esValida(dia, mes, anio)) {
            std::cout << "[!] La fecha ingresada no existe." << std::endl;
            continue;
        }

        if (validarNacimiento && !Fecha::esFechaNacimientoValida(dia, mes, anio)) {
            std::cout << "[!] La fecha de nacimiento no es válida (puede ser futura o muy antigua)." << std::endl;
            continue;
        }

        if (validarTurno) {
            Fecha fechaTmp(dia, mes, anio);
            if (!fechaTmp.esFechaTurnoValida()) {
                std::cout << "[!] La fecha del turno no es válida (no puede ser anterior a hoy)." << std::endl;
                continue;
            }
        }

        return Fecha(dia, mes, anio);
    }
}

