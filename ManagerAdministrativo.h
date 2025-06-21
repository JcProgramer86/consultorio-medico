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

    /// Método que calcula la facturación total del mes indicado (mes y año)
    float obtenerFacturacionDelMes();
    // metodo que listas los pacientes por especialidad x mes
    void listarPacientesAtendidosPorEspecialidadYMes();
    //Inicio submenu de ocupacion medica
    void ocupacionPorDiaDeMedico();
     void ocupacionPorMesDeMedico();
    ///
    int buscarEspecialidadPorNombre(const char* nombreEspecialidad);
    //para poder pedir la ocupacion por especilidad escribiendo el nombre y no el id
     void ocupacionPorMesEspecialidad();

private:
	 // Función auxiliar para comparar strings sin importar mayúsculas/minúsculas//es privada porque la uso dentro de la clase y no es accesible desde fuera
    bool compararStringsCaseInsensitive(const std::string& str1, const std::string& str2);
};
