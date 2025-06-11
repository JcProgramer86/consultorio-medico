#include "Hora.h"
#include <sstream>

Hora::Hora() {
    _hora = 0;
    _minuto = 0;
}


Hora::Hora(int hora, int minuto) {
    setHora(hora);
    setMinuto(minuto);
}

// Setters
void Hora::setHora(int hora) {
    if (hora >= 0 && hora < 24) {
        _hora = hora;
    } else {
        _hora = 0;
    }
}

void Hora::setMinuto(int minuto) {
    if (minuto >= 0 && minuto < 60) {
        _minuto = minuto;
    } else {
        _minuto = 0;
    }
}

// Getters
int Hora::getHora() const {
    return _hora;
}

int Hora::getMinuto() const {
    return _minuto;
}

bool Hora::operator==(const Hora& other) const {
    return _hora == other._hora && _minuto == other._minuto;
}


std::string Hora::toString() const {
    std::ostringstream oss;
    if (_hora < 10) oss << "0";
    oss << _hora << ":";
    if (_minuto < 10) oss << "0";
    oss << _minuto;
    return oss.str();
}

