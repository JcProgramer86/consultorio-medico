#include "ManagerAdministrativo.h"
#include "ArchivoTurno.h"
#include "ArchivoMedicoEspecialidad.h"
#include "ArchivoPaciente.h"
#include "ArchivoMedico.h"
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
    if (!Fecha::esValida(1, mes, anio)) {
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

    if (!Fecha::esValida(1, mes, anio)) {
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
