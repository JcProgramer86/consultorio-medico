#include "Paciente.h"


Paciente::Paciente() : Persona() {
    _idPrestador = 0;
}


Paciente::Paciente(int id, std::string dni, std::string nombre, std::string apellido,
                   std::string telefono, std::string email,
                   int idPrestador, Fecha fechaNacimiento)
    : Persona(id, dni, nombre, apellido, telefono, email, fechaNacimiento)
{
    _idPrestador = idPrestador;
}


int Paciente::get_idPrestador() {
    return _idPrestador;
}

void Paciente::set_idPrestador(int idPrestador) {
    _idPrestador = idPrestador;
}
