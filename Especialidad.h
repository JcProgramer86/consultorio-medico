#pragma once
#include <string> // Necesario para std::string en getNombre()
#include <cstring> // Necesario para strncpy

class Especialidad {
private:
    int _id;
    char _codEspecialidad[10];   // Código de la especialidad (ej: "CARDIO", "PEDIA")
    char _nombreEspecialidad[100]; // Nombre completo de la especialidad (ej: "Cardiología", "Pediatría")

public:
    // Constructor por defecto
    Especialidad();
    // Constructor parametrizado
    Especialidad(int id, const char* codEspecialidad, const char* nombreEspecialidad);

    // Getters (métodos const para no modificar el objeto)
    int getId() const;
    const char* getCodEspecialidad() const; // Retorna un puntero a char const
    const char* getNombreEspecialidad() const; // Retorna un puntero a char const

    // Setters
    void setId(int id);
    void setCodEspecialidad(const char* codEspecialidad);
    void setNombreEspecialidad(const char* nombreEspecialidad);
};
