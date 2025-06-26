#pragma once
#include <string>
#include "Especialidad.h"
#include "Turnos.h"
#include "ArchivoTurno.h"
#include "Fecha.h"

class ManagerAdministrativo
{
public:
    ManagerAdministrativo();

    float obtenerFacturacionDelMes();
    void listarPacientesAtendidosPorEspecialidadYMes();
    void ocupacionPorDiaDeMedico();
    void ocupacionPorMesAnioDeMedico();

    int buscarEspecialidadPorNombre(const char* nombreEspecialidad);
    void ocupacionPorMesEspecialidad();
    void ocupacionTotalPorMes();

private:
    bool compararStringsCaseInsensitive(const std::string& str1, const std::string& str2);

    // Funciones privadas para validar entradas con opción a salir
     // Función para pedir mes y año con validación y opción a cancelar
    bool pedirMesAnio(int &mes, int &anio);
    bool pedirDNI(std::string &dni);
};
