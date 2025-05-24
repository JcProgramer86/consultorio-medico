#include "Especialidad.h"
#include <cstring> // Para strcpy y strncpy

// Constructor por defecto
Especialidad::Especialidad() {
    _id = 0;
    _codEspecialidad[0] = '\0';   // Inicializa la cadena vacía
    _nombreEspecialidad[0] = '\0'; // Inicializa la cadena vacía
}

// Constructor parametrizado
Especialidad::Especialidad(int id, const char* codEspecialidad, const char* nombreEspecialidad) {
    _id = id;
    setCodEspecialidad(codEspecialidad);
    setNombreEspecialidad(nombreEspecialidad);
}

// Getters
int Especialidad::getId() const {
    return _id;
}

const char* Especialidad::getCodEspecialidad() const {
    return _codEspecialidad;
}

const char* Especialidad::getNombreEspecialidad() const {
    return _nombreEspecialidad;
}

// Setters
void Especialidad::setId(int id) {
    _id = id;
}

void Especialidad::setCodEspecialidad(const char* codEspecialidad) {
    // Copia la cadena de forma segura, evitando desbordamientos de búfer
    strncpy(_codEspecialidad, codEspecialidad, sizeof(_codEspecialidad) - 1);
    _codEspecialidad[sizeof(_codEspecialidad) - 1] = '\0'; // Asegura la terminación nula
}

void Especialidad::setNombreEspecialidad(const char* nombreEspecialidad) {
    // Copia la cadena de forma segura, evitando desbordamientos de búfer
    strncpy(_nombreEspecialidad, nombreEspecialidad, sizeof(_nombreEspecialidad) - 1);
    _nombreEspecialidad[sizeof(_nombreEspecialidad) - 1] = '\0'; // Asegura la terminación nula
}
