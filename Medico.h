#pragma once
#include "Persona.h"
#include "Fecha.h"

class Medico : public Persona {
private:
    int _idEspecialidad;
    Fecha _fechaInicioActividad;
    char _matricula[30];
    bool _enabled;

public:
    Medico();
    Medico(int id, std::string dni, std::string nombre, std::string apellido,
           std::string telefono, std::string email, Fecha fechaNacimiento,
           int idEspecialidad, Fecha fechaInicioActividad, std::string matricula, bool enabled);

    int get_idEspecialidad();
    Fecha get_fechaInicioActividad();
    std::string get_matricula();
    bool get_enabled();

    void set_idEspecialidad(int idEspecialidad);
    void set_fechaInicioActividad(Fecha fecha);
    void set_matricula(std::string matricula);
    void set_enabled(bool val);

    std::string toCSV();
};

