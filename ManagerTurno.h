#pragma once
#include "Turnos.h"

class ManagerTurno {

public:
    void sacarTurno();
    void mostrarAgendaSemanal();
    void listarTurnos();
    void listarTurnosPorPaciente();
    void listarTurnosPorDia();
    void listarTurnosPorSemana();
    void listarTurnosPorMes();

private:

    void mostrarTurnoResumen(Turno turno);
    void mostrarTurnoDetalle(Turno turno);

};

