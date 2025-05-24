#include "Hora.h"


Hora::Hora() {
    _hora = 0;
    _minuto = 0;
}
Hora::Hora(int hora, int minuto) {
    setHoraAtencion(hora);
    setMinutoAtencion(minuto);
}

// Setters
void Hora::setHoraAtencion(int hora) {
    if (hora >= 0 && hora < 24) {
        _hora = hora;
    } else {
        _hora = 0;
    }
}

void Hora::setMinutoAtencion(int minuto) {
    if (minuto >= 0 && minuto < 60) {
        _minuto = minuto;
    } else {
        _minuto = 0;
    }
}

// Getters
int Hora::getHoraAtencion() const {
    return _hora;
}

int Hora::getMinutoAtencion() const {
    return _minuto;
}
