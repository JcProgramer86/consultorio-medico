#include "Medico.h"
#include <cstring>  // Para strncpy

// Constructor por defecto
Medico::Medico() : Persona() {
    _idEspecialidad = 0;
    _fechaInicioActividad = Fecha();
    strcpy(_matricula, "");
    _enabled = true; // Por defecto habilitado
}

// Constructor con parámetros
Medico::Medico(int id, std::string dni, std::string nombre, std::string apellido,
               std::string telefono, std::string email, Fecha fechaNacimiento,
               int idEspecialidad, Fecha fechaInicioActividad, std::string matricula, bool enabled)
    : Persona(id, dni, nombre, apellido, telefono, email, fechaNacimiento),
      _idEspecialidad(idEspecialidad),
      _fechaInicioActividad(fechaInicioActividad),
      _enabled(enabled)
{
    set_matricula(matricula);
}

// Getters
int Medico::get_idEspecialidad() {
    return _idEspecialidad;
}

Fecha Medico::get_fechaInicioActividad() {
    return _fechaInicioActividad;
}

std::string Medico::get_matricula() {
    return std::string(_matricula);
}

bool Medico::get_enabled() {
    return _enabled;
}

// Setters
void Medico::set_idEspecialidad(int idEspecialidad) {
    _idEspecialidad = idEspecialidad;
}

void Medico::set_fechaInicioActividad(Fecha fecha) {
    _fechaInicioActividad = fecha;
}

void Medico::set_matricula(std::string matricula) {
    strncpy(_matricula, matricula.c_str(), sizeof(_matricula) - 1);
    _matricula[sizeof(_matricula) - 1] = '\0'; // Asegura terminación nula
}

void Medico::set_enabled(bool val) {
    _enabled = val;
}

// Exportar como CSV
std::string Medico::toCSV() {
    return std::to_string(get_id()) + "," +
           get_dni() + "," +
           get_nombre() + "," +
           get_apellido() + "," +
           get_telefono() + "," +
           get_email() + "," +
           get_fechaNacimiento().toString() + "," +
           std::to_string(get_idEspecialidad()) + "," +
           get_fechaInicioActividad().toString() + "," +
           get_matricula() + "," +
           (get_enabled() ? "1" : "0");
}
