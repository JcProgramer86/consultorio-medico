#include "Hora.h"


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
