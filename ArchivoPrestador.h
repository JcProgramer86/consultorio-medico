#pragma once
#include <string>
#include "Prestador.h"

class ArchivoPrestador{
    private:
        std::string _nombreArchivo;

    public:
        ArchivoPrestador(std::string nombreArchivo);
        bool Guardar(Prestador prestador);
        bool Guardar(Prestador prestador, int posicion);
        int Buscar(int IDPrestador);
        Prestador Leer(int posicion);
        int CantidadRegistros();
        void Leer(int cantidadRegistros, Prestador *vector);
};
