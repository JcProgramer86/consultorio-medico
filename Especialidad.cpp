#include "Especialidad.h"
#include <iostream>
#include <cstring>
#include <cctype>  // Para usar tolower

using namespace std;

// Constructor por defecto
Especialidad::Especialidad() {
    _id = 0;
    strcpy(_codEspecialidad, "");
    strcpy(_nombreEspecialidad, "");
    _enabled = true;  // Por defecto está habilitada
}

// Constructor con parámetros
Especialidad::Especialidad(int id, std::string nombre, bool enabled) {
    _id = id;
    set_nombreEspecialidad(nombre);
    generarCodigoEspecialidad(nombre, 1);
    _enabled = enabled;
}

// SETTERS

void Especialidad::set_id(int id) {
    _id = id;
}

void Especialidad::set_codEspecialidad(std::string codigo) {
    strncpy(_codEspecialidad, codigo.c_str(), sizeof(_codEspecialidad) - 1);
    _codEspecialidad[sizeof(_codEspecialidad) - 1] = '\0';
}

void Especialidad::set_nombreEspecialidad(std::string nombre) {
    strncpy(_nombreEspecialidad, nombre.c_str(), sizeof(_nombreEspecialidad) - 1);
    _nombreEspecialidad[sizeof(_nombreEspecialidad) - 1] = '\0';
}

void Especialidad::set_enabled(bool enabled) {
    _enabled = enabled;
}

// GETTERS

int Especialidad::get_id() {
    return _id;
}

char* Especialidad::get_codEspecialidad() {
    return _codEspecialidad;
}

char* Especialidad::get_nombreEspecialidad() {
    return _nombreEspecialidad;
}

bool Especialidad::get_enabled() {
    return _enabled;
}

// MÉTODO PARA GENERAR CÓDIGO
std::string Especialidad::generarCodigoEspecialidad(const std::string& nombre, int numeroSecuencia) {
    if (nombre.length() < 3) {
        std::cout << "[!] Nombre demasiado corto para generar un código." << std::endl;
        return "";
    }

    std::string sufijo = nombre.substr(0, 5);
    for (char& c : sufijo) {
        c = tolower(c);
    }

    char bufferNum[4];
    snprintf(bufferNum, sizeof(bufferNum), "%03d", numeroSecuencia);

    std::string codigo = std::string(bufferNum) + sufijo;

    strncpy(_codEspecialidad, codigo.c_str(), sizeof(_codEspecialidad) - 1);
    _codEspecialidad[sizeof(_codEspecialidad) - 1] = '\0';

    return codigo;
}
