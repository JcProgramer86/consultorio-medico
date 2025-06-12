#include "Paciente.h"
#include <iomanip>

Paciente::Paciente() : Persona() {
    _idPrestador = 0;
}

Paciente::Paciente(int id, std::string dni, std::string nombre, std::string apellido,
                   std::string telefono, std::string email,
                   int idPrestador, Fecha fechaNacimiento,
                   bool enabled)
    : Persona(id, dni, nombre, apellido, telefono, email, fechaNacimiento, enabled)
{
    _idPrestador = idPrestador;
}

int Paciente::get_idPrestador() const {
    return _idPrestador;
}

void Paciente::set_idPrestador(int idPrestador) {
    _idPrestador = idPrestador;
}

std::string Paciente::toCSV() const {
    return std::to_string(get_id()) + "," +
           get_dni() + "," +
           get_nombre() + "," +
           get_apellido() + "," +
           get_telefono() + "," +
           get_email() + "," +
           get_fechaNacimiento().toString() + "," +
           std::to_string(get_idPrestador()) + "," +
           (get_enabled() ? "1" : "0");
}
