#pragma once
#include <string>
#include "Medico.h"

class ArchivoMedico{
    private:
        std::string _nombreArchivoMedico;

    public:
        ArchivoMedico(std::string nombreArchivoMedico);
        bool Guardar(Medico Medico);
        bool Guardar(Medico Medico, int posicion);
        int Buscar(int IDMedico);
        Medico Leer(int posicion);
        int CantidadRegistros();
        void Leer(int cantidadRegistros, Medico *vector);
};
