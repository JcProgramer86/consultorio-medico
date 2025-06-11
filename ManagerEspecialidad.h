#pragma once
#include <string>
#include "Especialidad.h"

class ArchivoEspecialidad {
private:
    std::string _nombreArchivo;

public:
    // Constructor
    ArchivoEspecialidad(const std::string& nombreArchivo);

    // Métodos
    bool Guardar(const Especialidad& especialidad);
    bool Guardar(const Especialidad& especialidad, int posicion);
    Especialidad Leer(int posicion);
    int Buscar(int idEspecialidad);
    int CantidadRegistros();
    void Leer(int cantidadRegistros, Especialidad* vector);
    int generarNuevoId();
};
