#include "Medico.h"


Medico::Medico() : Persona() {
    _idEspecialidad = 0;
    _fechaInicioActividad = Fecha();
}


Medico::Medico(int id, std::string dni, std::string nombre, std::string apellido,
                   std::string telefono, std::string email,Fecha fechaNacimiento, int idEspecialidad,Fecha fechaInicioActividad)
                    : Persona(id, dni, nombre, apellido, telefono, email, fechaNacimiento){

        _idEspecialidad = idEspecialidad;
        _fechaInicioActividad = fechaInicioActividad;

    }


int Medico::get_idEspecialidad() {
    return _idEspecialidad;
}

Fecha Medico::get_fechaInicioActividad(){
    return _fechaInicioActividad;
}

void Medico::set_idEspecialidad(int idEspecialidad) {
    _idEspecialidad = idEspecialidad;
}

void Medico::set_fechaInicioActividad(Fecha fecha){
    _fechaInicioActividad = fecha;
}

std::string Medico::toCSV() { return std::to_string(get_id()) + "," + get_dni() + "," + get_nombre() + "," + get_apellido() + "," + get_telefono() + "," + get_email() + "," + get_fechaNacimiento().toString() + "," + std::to_string(get_idEspecialidad()) + "," + get_fechaInicioActividad().toString(); }

