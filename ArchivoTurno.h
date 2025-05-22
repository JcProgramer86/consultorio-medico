#pragma once

#include "Turnos.h"

class ArchivoTurno {
private:
    char _nombreArchivoTurno[50];  // Nombre del archivo para almacenar los turnos

public:
    ArchivoTurno(const char* nombreArchivoTurno);

    bool GuardarTurno(Turno turno);                   // Guarda un turno al final del archivo
    bool ModificarTurno(Turno turno, int posicion);  // Modifica un turno en la posición indicada
    int BuscarTurnoPorId(int idTurno);                // Busca turno por id, devuelve posición o -1 si no existe
    void ListarTurnos();                              // Lista todos los turnos (podría imprimirlos o devolverlos)
    bool LeerTurno(Turno& turno, int posicion);

};
