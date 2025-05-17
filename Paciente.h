#pragma once
#include "Persona.h"
#include "Fecha.h"

class Paciente : public Persona {
private:
    int _idPrestador;

public:
    Paciente();

    Paciente(int idPersona, std::string dni, std::string nombre, std::string apellido,
             std::string telefono, std::string email,
             int idPrestador, Fecha fechaNacimiento);

    int get_idPrestador();
    void set_idPrestador(int idPrestador);
};
