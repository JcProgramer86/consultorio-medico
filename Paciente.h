#pragma once
#pragma once
#include "Persona.h"
#include "Fecha.h"

class Paciente : public Persona {
private:
    int _idPrestador;

public:
    Paciente();

    Paciente(int id, std::string dni, std::string nombre, std::string apellido,
             std::string telefono, std::string email,
             int idPrestador, Fecha fechaNacimiento,
             bool enabled = true);

    int get_idPrestador() const;           // agregado const
    void set_idPrestador(int idPrestador);
    std::string toCSV() const;             // agregado const
};
