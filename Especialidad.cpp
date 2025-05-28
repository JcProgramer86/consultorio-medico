#include "Especialidad.h"
#include <iostream>
#include <cstring>
#include <cctype>  // Necesario para usar toupper

using namespace std;

// Constructor por defecto
// Inicializo los atributos vacíos o en 0
Especialidad::Especialidad() {
    _id = 0;
    strcpy(_codEspecialidad, "");         // Copio cadena vacía al array de char
    strcpy(_nombreEspecialidad, "");
}

// Constructor con parámetros
// Recibe un id y el nombre de la especialidad
Especialidad::Especialidad(int id, std::string nombre) {
    _id = id;
    set_nombreEspecialidad(nombre);       // Uso el setter para guardar el nombre
    generarCodigoEspecialidad(nombre, 1); // Llamo al método para generar el código con número 001 por ejemplo
}

// SETTERS

// Asigno directamente el ID
void Especialidad::set_id(int id) {
    _id = id;
}

// Este setter copia el string recibido al array de char _codEspecialidad
void Especialidad::set_codEspecialidad(std::string codigo) {
    // Copio usando strncpy para limitar el tamaño al array
    strncpy(_codEspecialidad, codigo.c_str(), sizeof(_codEspecialidad) - 1);

    // Me aseguro de que la cadena termine en '\0'
    _codEspecialidad[sizeof(_codEspecialidad) - 1] = '\0';
}

// Igual que el anterior, pero para el nombre
void Especialidad::set_nombreEspecialidad(std::string nombre) {
    strncpy(_nombreEspecialidad, nombre.c_str(), sizeof(_nombreEspecialidad) - 1);
    _nombreEspecialidad[sizeof(_nombreEspecialidad) - 1] = '\0';
}

// GETTERS

int Especialidad::get_id() {
    return _id;
}

// Devuelvo el puntero al array de char (cadena C)
char* Especialidad::get_codEspecialidad() {
    return _codEspecialidad;
}

char* Especialidad::get_nombreEspecialidad() {
    return _nombreEspecialidad;
}

// MÉTODO PARA GENERAR CÓDIGO DE ESPECIALIDAD
// Recibe el nombre y un número correlativo (por ejemplo: 1 para 001, 2 para 002, etc.)
void Especialidad::generarCodigoEspecialidad(std::string nombre, int numeroSecuencia) {
    if (nombre.length() < 3) {
        std::cout << "El nombre de la especialidad es muy corto para generar un código." << std::endl;
        return;
    }

    std::string codigo = "";
    for (int i = 0; i < 3; i++) {
        // Convertimos a mayúscula directamente, sin static_cast
        codigo += toupper(nombre[i]);
    }

    if (numeroSecuencia < 10) {
        codigo += "-00" + std::to_string(numeroSecuencia);
    } else if (numeroSecuencia < 100) {
        codigo += "-0" + std::to_string(numeroSecuencia);
    } else {
        codigo += "-" + std::to_string(numeroSecuencia);
    }

    strncpy(_codEspecialidad, codigo.c_str(), sizeof(_codEspecialidad) - 1);
    _codEspecialidad[sizeof(_codEspecialidad) - 1] = '\0';

    std::cout << "Código generado: " << _codEspecialidad << std::endl;
}
