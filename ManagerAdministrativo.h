#pragma once
#include "Medico.h"
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
    void ocupacionPorMesDeMedico();
    void ocupacionPorMesEspecialidad();
    void ocupacionTotalPorMes();

    int buscarEspecialidadPorNombre(const char* nombreEspecialidad);
    int pedirEspecialidad();

private:
    bool compararStringsCaseInsensitive(const std::string& str1, const std::string& str2);
    bool pedirMesAnio(int& mes, int& anio);
    int obtenerIdMedicoPorDni(const std::string& dni);
    int obtenerIdPacientePorDni(const std::string& dni);

    void mostrarEspecialidades();


};
