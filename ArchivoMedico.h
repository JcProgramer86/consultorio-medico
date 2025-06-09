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
        int BuscarPorDni( const std::string& dniMedico);
        Medico Leer(int posicion);
        int CantidadRegistros();
        int generarNuevoId();
        void Leer(int cantidadRegistros, Medico *vector);

        bool checkDni(std::string& dni);
};
