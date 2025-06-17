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
std::string Especialidad::generarCodigoEspecialidad(const std::string& nombre, int numeroSecuencia) {
    if (nombre.length() < 3) {
        std::cout << "El nombre de la especialidad es muy corto para generar un código." << std::endl;
        return "";
    }

    // Obtener primeros 5 caracteres del nombre en minúscula
    std::string sufijo = nombre.substr(0, 5);
    for (char& c : sufijo) {
        c = tolower(c);
    }

    // Generar número con 3 dígitos
    char bufferNum[4];
    snprintf(bufferNum, sizeof(bufferNum), "%03d", numeroSecuencia);

    // Concatenar número + sufijo
    std::string codigo = std::string(bufferNum) + sufijo;

    // Guardar en el atributo (por compatibilidad si también lo usás así)
    strncpy(_codEspecialidad, codigo.c_str(), sizeof(_codEspecialidad) - 1);
    _codEspecialidad[sizeof(_codEspecialidad) - 1] = '\0';

    return codigo;
}


