#include "Medico.h"
#include <cstring>

Medico::Medico() : Persona()
{
    _idEspecialidad = 0;
    _fechaInicioActividad = Fecha();
    strcpy(_matricula, "");
}

Medico::Medico(int id, std::string dni, std::string nombre, std::string apellido,
               std::string telefono, std::string email, Fecha fechaNacimiento,
               int idEspecialidad, Fecha fechaInicioActividad, std::string matricula)
    : Persona(id, dni, nombre, apellido, telefono, email, fechaNacimiento),
      _idEspecialidad(idEspecialidad),
      _fechaInicioActividad(fechaInicioActividad)
{
    set_matricula(matricula); // Para el arreglo char[], se hace aquí
}

int Medico::get_idEspecialidad()
{
    return _idEspecialidad;
}

Fecha Medico::get_fechaInicioActividad()
{
    return _fechaInicioActividad;
}

std::string Medico::get_matricula()
{
    return std::string(_matricula);
}

void Medico::set_matricula(std::string matricula)
{
    strncpy(_matricula, matricula.c_str(), sizeof(_matricula) - 1);
    _matricula[sizeof(_matricula) - 1] = '\0'; // Asegura el fin de cadena
}

void Medico::set_idEspecialidad(int idEspecialidad)
{
    _idEspecialidad = idEspecialidad;
}

void Medico::set_fechaInicioActividad(Fecha fecha)
{
    _fechaInicioActividad = fecha;
}

std::string Medico::toCSV()
{
    return std::to_string(get_id()) + "," +
           get_dni() + "," +
           get_nombre() + "," +
           get_apellido() + "," +
           get_telefono() + "," +
           get_email() + "," +
           get_fechaNacimiento().toString() + "," +
           std::to_string(get_idEspecialidad()) + "," +
           get_fechaInicioActividad().toString() + "," +
           get_matricula(); // AHORA INCLUYE LA MATRÍCULA
}
