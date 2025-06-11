#pragma once
#include <string>
#include "Turnos.h"

class ArchivoTurno {
private:
    std::string _nombreArchivoTurno;

public:
    ArchivoTurno(std::string nombreArchivoTurno);

    bool Guardar(Turno turno);
    bool Guardar(Turno turno, int posicion);
    int Buscar(int IDTurno);
    Turno Leer(int posicion);
    int CantidadRegistros();
    int generarNuevoId();
    void Leer(int cantidadRegistros, Turno* vector);
    void ListarTurnos();
};
