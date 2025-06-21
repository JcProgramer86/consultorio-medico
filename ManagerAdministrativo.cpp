#include "ManagerAdministrativo.h"
#include "ArchivoTurno.h"
#include "ArchivoMedicoEspecialidad.h"
#include "ArchivoPaciente.h"
#include "ArchivoMedico.h"
#include <cstring>
#include <cctype>
#include "ArchivoEspecialidad.h"
#include "Especialidad.h"
#include <iostream>
#include <iomanip>
using namespace std;

ManagerAdministrativo::ManagerAdministrativo()
{
    // Constructor vacío
}

// Obtener facturación total de un mes y año
float ManagerAdministrativo::obtenerFacturacionDelMes()
{
    int mes, anio;
    cout << "Ingrese el mes (1-12): ";
    cin >> mes;
    cout << "Ingrese el anio: ";
    cin >> anio;

    // Validar mes y año (día fijo 1 para validar solo mes/año)
    if (!Fecha::esValida(1, mes, anio))
    {
        cout << "Mes o año inválido.\n";
        system("pause");
        return 0.0f;
    }

    ArchivoTurno archivoTurno("turnos.dat");
    float totalFacturacion = 0.0f;
    int cantidadTurnos = archivoTurno.CantidadRegistros();

    for (int i = 0; i < cantidadTurnos; i++)
    {
        Turno turno = archivoTurno.Leer(i);
        Fecha fecha = turno.getFechaAtencion();

        if (fecha.getMes() == mes && fecha.getAnio() == anio
                && !turno.getCancelado()
                && turno.getAsistio())
        {
            totalFacturacion += turno.getImporteConsulta();
        }
    }

    cout << fixed << setprecision(2);
    cout << "Facturación total para " << mes << "/" << anio << ": $ " << totalFacturacion << endl;
    system("pause");

    return totalFacturacion;
}

// Listar pacientes atendidos por especialidad en un mes y año
void ManagerAdministrativo::listarPacientesAtendidosPorEspecialidadYMes()
{
    int mes, anio, idEspecialidad;
    cout << "Ingrese el mes (1-12): ";
    cin >> mes;
    cout << "Ingrese el año: ";
    cin >> anio;
    cout << "Ingrese el ID de especialidad: ";
    cin >> idEspecialidad;

    if (!Fecha::esValida(1, mes, anio))
    {
        cout << "Mes o año inválido.\n";
        system("pause");
        return;
    }

    ArchivoTurno archivoTurno("turnos.dat");
    ArchivoMedicoEspecialidad archivoMedicoEspecialidad("medicoespecialidad.dat");
    ArchivoPaciente archivoPaciente("paciente.dat");

    int cantidadTurnos = archivoTurno.CantidadRegistros();
    bool hayPacientes = false;

    cout << "\nPacientes atendidos en " << mes << "/" << anio << " para especialidad ID " << idEspecialidad << ":\n";

    for (int i = 0; i < cantidadTurnos; i++)
    {
        Turno turno = archivoTurno.Leer(i);
        Fecha fecha = turno.getFechaAtencion();

        if (turno.getAsistio() && !turno.getCancelado() &&
                fecha.getMes() == mes && fecha.getAnio() == anio)
        {
            int posMedicoEsp = archivoMedicoEspecialidad.Buscar(turno.getIdMedicoEspecialidad());
            if (posMedicoEsp != -1)
            {
                MedicoEspecialidad medicoEsp = archivoMedicoEspecialidad.Leer(posMedicoEsp);

                if (medicoEsp.getIdEspecialidad() == idEspecialidad)
                {
                    int posPaciente = archivoPaciente.Buscar(turno.getIdPaciente());
                    if (posPaciente != -1)
                    {
                        Paciente paciente = archivoPaciente.Leer(posPaciente);
                        cout << "- " << paciente.get_nombre() << " " << paciente.get_apellido()
                             << " (ID: " << paciente.get_id() << ")\n";
                        hayPacientes = true;
                    }
                }
            }
        }
    }

    if (!hayPacientes)
    {
        cout << "No se encontraron pacientes atendidos en esa especialidad y mes.\n";
    }

    system("pause");
}

// Opción 1: Ocupación por día de un médico (por DNI)
void ManagerAdministrativo::ocupacionPorDiaDeMedico()
{
    string dniMedico;
    int dia, mes, anio;

    cout << "Ingrese el DNI del médico: ";
    cin >> dniMedico;

    Persona personaAux;
    if (!personaAux.validarDNI(dniMedico))
    {
        cout << "DNI inválido.\n";
        system("pause");
        return;
    }

    cout << "Ingrese el día (1-31): ";
    cin >> dia;
    cout << "Ingrese el mes (1-12): ";
    cin >> mes;
    cout << "Ingrese el año: ";
    cin >> anio;

    if (!Fecha::esValida(dia, mes, anio))
    {
        cout << "Fecha inválida.\n";
        system("pause");
        return;
    }

    ArchivoTurno archivoTurno("turnos.dat");
    ArchivoMedico archivoMedico("medico.dat");

    int idMedico = -1;
    int cantidadMedicos = archivoMedico.CantidadRegistros();
    for (int i = 0; i < cantidadMedicos; i++)
    {
        Medico medico = archivoMedico.Leer(i);
        if (medico.get_dni() == dniMedico)
        {
            idMedico = medico.get_id();
            break;
        }
    }

    if (idMedico == -1)
    {
        cout << "Médico con DNI " << dniMedico << " no encontrado.\n";
        system("pause");
        return;
    }

    int turnosEnElDia = 0;
    int cantidadTurnos = archivoTurno.CantidadRegistros();

    for (int i = 0; i < cantidadTurnos; i++)
    {
        Turno turno = archivoTurno.Leer(i);
        Fecha fecha = turno.getFechaAtencion();

        if (turno.getIdMedicoEspecialidad() == idMedico &&
                fecha.getDia() == dia &&
                fecha.getMes() == mes &&
                fecha.getAnio() == anio &&
                !turno.getCancelado() &&
                turno.getAsistio())
        {
            turnosEnElDia++;
        }
    }

    cout << "\n" << left << setw(30) << "DNI del Médico:" << dniMedico << endl;
    cout << left << setw(30) << "Fecha Consultada:" << dia << "/" << mes << "/" << anio << endl;
    cout << left << setw(30) << "Turnos Atendidos:" << turnosEnElDia << "\n" << endl;

    system("pause");
}

// Opción 2: Ocupación por mes de un médico (por DNI)
void ManagerAdministrativo::ocupacionPorMesDeMedico()
{
    string dniMedico;
    int mes, anio;

    cout << "Ingrese el DNI del médico: ";
    cin >> dniMedico;

    Persona personaAux;
    if (!personaAux.validarDNI(dniMedico))
    {
        cout << "DNI inválido.\n";
        system("pause");
        return;
    }

    cout << "Ingrese el mes (1-12): ";
    cin >> mes;
    cout << "Ingrese el año: ";
    cin >> anio;

    if (!Fecha::esValida(1, mes, anio))
    {
        cout << "Mes o año inválido.\n";
        system("pause");
        return;
    }

    ArchivoTurno archivoTurno("turnos.dat");
    ArchivoMedico archivoMedico("medico.dat");

    int idMedico = -1;
    int cantidadMedicos = archivoMedico.CantidadRegistros();
    for (int i = 0; i < cantidadMedicos; i++)
    {
        Medico medico = archivoMedico.Leer(i);
        if (medico.get_dni() == dniMedico)
        {
            idMedico = medico.get_id();
            break;
        }
    }

    if (idMedico == -1)
    {
        cout << "Médico con DNI " << dniMedico << " no encontrado.\n";
        system("pause");
        return;
    }

    int cantidadTurnos = archivoTurno.CantidadRegistros();
    int turnosEnElMes = 0;

    for (int i = 0; i < cantidadTurnos; i++)
    {
        Turno turno = archivoTurno.Leer(i);
        Fecha fecha = turno.getFechaAtencion();

        if (turno.getIdMedicoEspecialidad() == idMedico &&
                fecha.getMes() == mes &&
                fecha.getAnio() == anio &&
                !turno.getCancelado() &&
                turno.getAsistio())
        {
            turnosEnElMes++;
        }
    }

    cout << "\n" << left << setw(30) << "DNI del Médico:" << dniMedico << endl;
    cout << left << setw(30) << "Mes Consultado:" << mes << "/" << anio << endl;
    cout << left << setw(30) << "Turnos Atendidos:" << turnosEnElMes << "\n" << endl;

    system("pause");
}

//Opcion 3  del menu buscando la especialidad x nombre y no por id
// Función auxiliar para comparar strings sin distinguir mayúsculas/minúsculas
bool ManagerAdministrativo::compararStringsCaseInsensitive(const std::string& str1, const std::string& str2)
{
    // Primero verifico que tengan la misma longitud
    if ((int)str1.length() != (int)str2.length())
    {
        return false;
    }

    for (int i = 0; i < (int)str1.length(); i++)
    {
        char c1 = str1[i];
        char c2 = str2[i];

        // Convertir c1 a minúscula si es mayúscula
        if (c1 >= 'A' && c1 <= 'Z')
        {
            c1 = c1 + 32;
        }

        // Convertir c2 a minúscula si es mayúscula
        if (c2 >= 'A' && c2 <= 'Z')
        {
            c2 = c2 + 32;
        }

        if (c1 != c2)
        {
            return false;
        }
    }

    return true;
}


int ManagerAdministrativo::buscarEspecialidadPorNombre(const char* nombreEspecialidad)
{
    ArchivoEspecialidad archivo("especialidad.dat");
    int cantidad = archivo.cantidadRegistros();
    Especialidad esp;

    for (int i = 0; i < cantidad; i++)
    {
        esp = archivo.leer(i);
        if (compararStringsCaseInsensitive(esp.get_nombreEspecialidad(), nombreEspecialidad))
        {
            return i;  // Retorna la posición si encontró la especialidad
        }
    }
    return -1; // No encontró la especialidad
}



void ManagerAdministrativo::ocupacionPorMesEspecialidad()
{
    int mes, anio;
    cout << "Ingrese el mes (1-12): ";
    cin >> mes;
    cout << "Ingrese el año (ej. 2025): ";
    cin >> anio;

    // Validar mes y añoion 3
    if (!Fecha::esValida(1, mes, anio))
    {
        cout << "Mes o año inválido.\n";
        return;
    }

    ArchivoTurno archivoTurno("turnos.dat");
    int cantidadTurnos = archivoTurno.CantidadRegistros();
    if (cantidadTurnos == 0)
    {
        cout << "No hay turnos registrados.\n";
        return;
    }

    ArchivoMedicoEspecialidad archivoMedEsp("medicoespecialidad.dat");
    ArchivoEspecialidad archivoEsp("especialidad.dat");

    // Contador de turnos por especialidad (asumiendo hasta 100 especialidades)
    const int MAX_ESPECIALIDADES = 100;
    int turnosPorEspecialidad[MAX_ESPECIALIDADES] = {0};

    int cantEspecialidades = archivoEsp.cantidadRegistros();
    if (cantEspecialidades == 0)
    {
        cout << "No hay especialidades registradas.\n";
        return;
    }

    // Recorro todos los turnos para contar los que coincidan con mes y año y no estén cancelados
    for (int i = 0; i < cantidadTurnos; i++)
    {
        Turno turno = archivoTurno.Leer(i);
        Fecha fecha = turno.getFechaAtencion();

        if (fecha.getMes() == mes && fecha.getAnio() == anio && !turno.getCancelado() && turno.getAsistio())
        {
            int idMedEsp = turno.getIdMedicoEspecialidad();
            // Busco la especialidad correspondiente a ese id medico-especialidad
            int cantMedEsp = archivoMedEsp.CantidadRegistros();
            for (int j = 0; j < cantMedEsp; j++)
            {
                MedicoEspecialidad medEsp = archivoMedEsp.Leer(j);
                if (medEsp.getId() == idMedEsp)
                {
                    int idEsp = medEsp.getIdEspecialidad();
                    // Incremento contador del id de especialidad si está dentro del rango
                    if (idEsp > 0 && idEsp <= MAX_ESPECIALIDADES)
                    {
                        turnosPorEspecialidad[idEsp - 1]++;
                    }
                    break;
                }
            }
        }
    }

    cout << "\nOcupación médica por especialidad para "
         << setw(2) << setfill('0') << mes << "/" << anio << ":\n";
    cout << setfill(' ') << left;
    cout << setw(30) << "Especialidad" << "Turnos\n";
    cout << "-------------------------------------------\n";

    // Muestro sólo las especialidades con al menos un turno
    for (int k = 0; k < cantEspecialidades; k++)
    {
        if (turnosPorEspecialidad[k] > 0)
        {
            Especialidad esp = archivoEsp.leer(k);
            cout << left << setw(30) << esp.get_nombreEspecialidad()
                 << turnosPorEspecialidad[k] << "\n";
        }
    }
}
//submenu 4 de ocupacion medica
void ManagerAdministrativo::ocupacionTotalPorMes()
{
    int mes, anio;
    cout << "Ingrese el mes (1-12): ";
    cin >> mes;
    cout << "Ingrese el año: ";
    cin >> anio;

    // Validar mes y año (día 1 para usar esValida)
    if (!Fecha::esValida(1, mes, anio))
    {
        cout << "Mes o año inválido.\n";
        system("pause");
        return;
    }

    ArchivoTurno archivoTurno("turnos.dat");
    int cantidadTurnos = archivoTurno.CantidadRegistros();
    if (cantidadTurnos == 0)
    {
        cout << "No hay turnos registrados.\n";
        system("pause");
        return;
    }

    ArchivoMedico archivoMedico("medico.dat");
    int cantidadMedicos = archivoMedico.CantidadRegistros();
    if (cantidadMedicos == 0)
    {
        cout << "No hay médicos registrados.\n";
        system("pause");
        return;
    }

    const int MAX_MEDICOS = 1000;
    int turnosPorMedico[MAX_MEDICOS] = {0};

    // Recorro todos los turnos y acumulo los válidos por id de médico
    for (int i = 0; i < cantidadTurnos; i++)
    {
        Turno turno = archivoTurno.Leer(i);
        Fecha fecha = turno.getFechaAtencion();

        if (!turno.getCancelado() &&
            turno.getAsistio() &&
            fecha.getMes() == mes &&
            fecha.getAnio() == anio)
        {
            int idMedico = turno.getIdMedicoEspecialidad();
            if (idMedico > 0 && idMedico <= MAX_MEDICOS)
            {
                turnosPorMedico[idMedico - 1]++;
            }
        }
    }

    cout << "\nOcupación total de todos los médicos para ";
    cout << setw(2) << setfill('0') << mes << "/" << anio << ":\n";

    cout << setfill(' ') << left;
    cout << setw(6) << "ID"
         << setw(15) << "DNI"
         << setw(20) << "Nombre"
         << setw(20) << "Apellido"
         << right << setw(10) << "Turnos" << "\n";
    cout << "------------------------------------------------------------------\n";

    bool hayDatos = false;
    for (int i = 0; i < cantidadMedicos; i++)
    {
        Medico medico = archivoMedico.Leer(i);
        int idMedico = medico.get_id();

        if (idMedico > 0 && idMedico <= MAX_MEDICOS && turnosPorMedico[idMedico - 1] > 0)
        {
            cout << left << setw(6) << idMedico
                 << setw(15) << medico.get_dni()
                 << setw(20) << medico.get_nombre()
                 << setw(20) << medico.get_apellido()
                 << right << setw(10) << turnosPorMedico[idMedico - 1] << "\n";
            hayDatos = true;
        }
    }

    if (!hayDatos)
    {
        cout << "No hubo turnos registrados para ningún médico en ese mes.\n";
    }

    cout << endl;
    system("pause");
}
