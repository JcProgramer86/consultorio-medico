#pragma once
#include "Especialidad.h"
#include <string>

class ArchivoEspecialidad {
private:
    std::string _nombreArchivo;

public:
    ArchivoEspecialidad(std::string nombreArchivo = "especialidades.dat");

    bool guardar(Especialidad especialidad);
    bool guardar(Especialidad especialidad, int posicion);
    int buscarPorCodigo(const char* codigo);
    int buscarPorId(int id);
    Especialidad leer(int posicion);
    void leer(int cantidadRegistros, Especialidad* vector);
    int cantidadRegistros();
    Especialidad leerPorId(int id);
};
