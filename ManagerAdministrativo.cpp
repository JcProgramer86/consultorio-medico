#include "ManagerAdministrativo.h"
#include "ArchivoTurno.h"
#include "ArchivoMedicoEspecialidad.h"
#include "ArchivoPaciente.h"
#include <iostream>
using namespace std;

ManagerAdministrativo::ManagerAdministrativo() {
    // Constructor vacío
}

float ManagerAdministrativo::obtenerFacturacionDelMes() {
    int mes, anio;
    cout << "Ingrese el mes (1-12): ";
    cin >> mes;
    cout << "Ingrese el anio: ";
    cin >> anio;

    ArchivoTurno archivoTurno("turnos.dat");
    float totalFacturacion = 0.0f;

    int cantidadTurnos = archivoTurno.CantidadRegistros();

    for (int i = 0; i < cantidadTurnos; i++) {
        Turno turno = archivoTurno.Leer(i);
        Fecha fecha = turno.getFechaAtencion();

        if (fecha.getMes() == mes && fecha.getAnio() == anio
            && !turno.getCancelado()
            && turno.getAsistio()) {   //  Ahora chequea que asistió
            totalFacturacion += turno.getImporteConsulta();
        }
    }

    cout << "La facturación del mes " << mes << "/" << anio << " es: $" << totalFacturacion << endl;
    system("pause");

    return totalFacturacion;
}


void ManagerAdministrativo::listarPacientesAtendidosPorEspecialidadYMes() {
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

    for (int i = 0; i < cantidadTurnos; i++) {
        Turno turno = archivoTurno.Leer(i);
        Fecha fecha = turno.getFechaAtencion();

        if (turno.getAsistio() && !turno.getCancelado() &&
            fecha.getMes() == mes && fecha.getAnio() == anio) {

            // Obtengo la relación médico-especialidad
            int posMedicoEsp = archivoMedicoEspecialidad.Buscar(turno.getIdMedicoEspecialidad());
            if (posMedicoEsp == -1) continue;

            MedicoEspecialidad medicoEsp = archivoMedicoEspecialidad.Leer(posMedicoEsp);

            if (medicoEsp.getIdEspecialidad() == idEspecialidad) {
                int posPaciente = archivoPaciente.Buscar(turno.getIdPaciente());
                if (posPaciente == -1) continue;

                Paciente paciente = archivoPaciente.Leer(posPaciente);

                cout << "- " << paciente.get_nombre() << " " << paciente.get_apellido()
                     << " (ID: " << paciente.get_id() << ")\n";
                hayPacientes = true;
            }
        }
    }

    if (!hayPacientes) {
        cout << "No se encontraron pacientes atendidos en esa especialidad y mes.\n";
    }

    system("pause");
}
