#pragma once
#include "Persona.h"
#include "Fecha.h"

class Medico : public Persona {

private:
    int _idEspecialidad;
    Fecha _fechaInicioActividad;

public:
    Medico();

    Medico(int id, std::string dni, std::string nombre, std::string apellido,
           std::string telefono, std::string email, Fecha fechaNacimiento,
           int idEspecialidad, Fecha fechaInicioActividad);

    void set_idEspecialidad(int idEspecialidad);
    void set_fechaInicioActividad(Fecha fecha);

    int get_idEspecialidad();
    Fecha get_fechaInicioActividad();
};
