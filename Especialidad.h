#pragma once
#include <string>

class Especialidad {
private:
    int _id;
    char _codEspecialidad[100];
    char _nombreEspecialidad[100];

public:
    // Constructor por defecto
    Especialidad();

    // Constructor con parámetros
    Especialidad(int id, std::string nombre);

    // Setters
    void set_id(int id);
    void set_codEspecialidad(std::string codigo);
    void set_nombreEspecialidad(std::string nombre);

    // Getters
    int get_id();
    char* get_codEspecialidad();
    char* get_nombreEspecialidad();

    // Método para generar el código automáticamente
    std::string generarCodigoEspecialidad(const std::string& nombre, int numeroSecuencia);

};
