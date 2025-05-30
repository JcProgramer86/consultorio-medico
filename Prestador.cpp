#include "Prestador.h"
#include <cstring>
#include <iostream>

int Prestador::_globalCounter = 0;

Prestador::Prestador() {
    _id = 0;
    _enabled = false;
    strcpy(_codPrestador,"");
    strcpy(_nombrePrestador,"");

}


Prestador::Prestador(int id,std::string codPrestador,std::string nombrePrestador,bool enabled){
    setId(id);
    setEnabled(enabled);
    setCodPrestador(codPrestador);
    setNombrePrestador(nombrePrestador);
}

// — Getters

int Prestador::getId() {
    return _id;
}

std::string Prestador::getCodPrestador(){
    return _codPrestador;
}

std::string Prestador::getNombrePrestador(){
    return _nombrePrestador;
}

bool Prestador::isEnabled(){
    return _enabled;
}

// — Setters

void Prestador::setId(int id) {
    _id = id;
}

void Prestador::setCodPrestador(std::string codPrestador) {
    strcpy(_codPrestador,codPrestador.c_str());
}

void Prestador::setNombrePrestador(std::string nombrePrestador) {
    strcpy(_nombrePrestador,nombrePrestador.c_str());
}

void Prestador::setEnabled(bool enabled) {
    _enabled = enabled;
}

void Prestador::generarCodigo(std::string& nombreObraSocial) {
    // 1) Extraer hasta 4 letras alfabéticas en mayúscula
    char prefijo[5];  // hasta 4 letras + '\0'
    int  prefLen = 0;
    for (size_t i = 0; i < nombreObraSocial.size() && prefLen < 4; ++i) {
        char ch = nombreObraSocial[i];
        // chequeo manual de letra
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            // convertir a mayúscula
            if (ch >= 'a' && ch <= 'z') {
                ch = ch - ('a' - 'A');
            }
            prefijo[prefLen++] = ch;
        }
    }
    prefijo[prefLen] = '\0';  // sin rellenar si <4

    // 2) Incrementar correlativo global
    int correlativo = ++_globalCounter;

    // 3) Convertir número a cadena
    char numStr[12];
    std::sprintf(numStr, "%d", correlativo);

    // 4) Construir el código completo
    //    longitud máxima 9 caracteres (10º para '\0')
    char codigo[10];
    int  idx = 0;
    // copiar el prefijo (3 o 4 letras)
    for (int j = 0; j < prefLen; ++j) {
        codigo[idx++] = prefijo[j];
    }
    // añadir dígitos, sin pasar de 9
    for (int j = 0; numStr[j] != '\0' && idx < 9; ++j) {
        codigo[idx++] = numStr[j];
    }
    codigo[idx] = '\0';

    // 5) Volcar en el miembro interno
    std::strncpy(_codPrestador, codigo, sizeof(_codPrestador)-1);
    _codPrestador[sizeof(_codPrestador)-1] = '\0';
}
