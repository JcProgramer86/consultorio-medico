#include "ManagerAdministrativo.h"
#include "ArchivoTurno.h"
#include "ArchivoMedicoEspecialidad.h"
#include "ArchivoPaciente.h"
#include "ArchivoMedico.h"
#include <iostream>
using namespace std;

ManagerAdministrativo::ManagerAdministrativo()
{
    // Constructor vacío
}

float ManagerAdministrativo::obtenerFacturacionDelMes()
{
    int mes, anio;
    cout << "Ingrese el mes (1-12): ";
    cin >> mes;
    cout << "Ingrese el anio: ";
    cin >> anio;

    ArchivoTurno archivoTurno("turnos.dat");
    float totalFacturacion = 0.0f;

    int cantidadTurnos = archivoTurno.CantidadRegistros();

    for (int i = 0; i < cantidadTurnos; i++)
    {
        Turno turno = archivoTurno.Leer(i);
        Fecha fecha = turno.getFechaAtencion();

        if (fecha.getMes() == mes && fecha.getAnio() == anio
                && !turno.getCancelado()
                && turno.getAsistio())     //  Ahora chequea que asistió
        {
            totalFacturacion += turno.getImporteConsulta();
        }
    }

    cout << "La facturación del mes " << mes << "/" << anio << " es: $" << totalFacturacion << endl;
    system("pause");

    return totalFacturacion;
}


void ManagerAdministrativo::listarPacientesAtendidosPorEspecialidadYMes()
{
    int mes, anio, idEspecialidad;
    cout << "Ingrese el mes (1-12): ";
    cin >> mes;
    cout << "Ingrese el año: ";
    cin >> anio;
    cout << "Ingrese el ID de especialidad: ";
    cin >> idEspecialidad;

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

            // Obtengo la relación médico-especialidad
            int posMedicoEsp = archivoMedicoEspecialidad.Buscar(turno.getIdMedicoEspecialidad());
            if (posMedicoEsp == -1) continue;

            MedicoEspecialidad medicoEsp = archivoMedicoEspecialidad.Leer(posMedicoEsp);

            if (medicoEsp.getIdEspecialidad() == idEspecialidad)
            {
                int posPaciente = archivoPaciente.Buscar(turno.getIdPaciente());
                if (posPaciente == -1) continue;

                Paciente paciente = archivoPaciente.Leer(posPaciente);

                cout << "- " << paciente.get_nombre() << " " << paciente.get_apellido()
                     << " (ID: " << paciente.get_id() << ")\n";
                hayPacientes = true;
            }
        }
    }

    if (!hayPacientes)
    {
        cout << "No se encontraron pacientes atendidos en esa especialidad y mes.\n";
    }

    system("pause");
}
/////// Aca haceos desarrollo de submenues de ocupacion medica


void ManagerAdministrativo::ocupacionPorDiaDeMedico()
{
    string dniMedico;
    int dia, mes, anio;

    cout << "Ingrese el DNI del médico: ";
    cin >> dniMedico;

    cout << "Ingrese el día (1-31): ";
    cin >> dia;

    cout << "Ingrese el mes (1-12): ";
    cin >> mes;

    cout << "Ingrese el año: ";
    cin >> anio;

    ArchivoTurno archivoTurno("turnos.dat");
    ArchivoMedico archivoMedico("medico.dat"); // para buscar médico por DNI

    int cantidadTurnos = archivoTurno.CantidadRegistros();
    int idMedico = -1;

    // Buscar el idMedico a partir del DNI
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

    for (int i = 0; i < cantidadTurnos; i++)
    {
        Turno turno = archivoTurno.Leer(i);
        Fecha fecha = turno.getFechaAtencion();

        if (turno.getIdMedicoEspecialidad() == idMedico &&  // en vez de turno.getId()
                fecha.getDia() == dia &&
                fecha.getMes() == mes &&
                fecha.getAnio() == anio &&
                !turno.getCancelado() &&
                turno.getAsistio())
        {
            turnosEnElDia++;
        }

    }

    cout << "El médico con DNI " << dniMedico << " tiene " << turnosEnElDia << " turnos en "
         << dia << "/" << mes << "/" << anio << ".\n";

    system("pause");
}
