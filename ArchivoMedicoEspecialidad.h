#pragma once
#include <string>
#include "MedicoEspecialidad.h"

class ArchivoMedicoEspecialidad{
    private:
        std::string _nombreArchivo;

    public:
        ArchivoMedicoEspecialidad(std::string nombreArchivoMedicoEspecialidad);
        bool Guardar(MedicoEspecialidad medicoEspecialidad);
        bool Guardar(MedicoEspecialidad medicoEspecialidad, int posicion);
        int Buscar(int idMedicoEspecialidad);
        MedicoEspecialidad Leer(int posicion);
        int CantidadRegistros();
        void Leer(int cantidadRegistros, MedicoEspecialidad *vector);
};
