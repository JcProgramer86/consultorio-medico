#pragma once

#include "Turnos.h"
#include "ArchivoTurno.h"
#include "Fecha.h"

class ManagerAdministrativo {
public:
    ManagerAdministrativo();

    /// Método que calcula la facturación total del mes indicado (mes y año)
    float obtenerFacturacionDelMes();
    // metodo que listas los pacientes por especialidad x mes
    void listarPacientesAtendidosPorEspecialidadYMes();

};
