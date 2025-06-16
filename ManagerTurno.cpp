#include "ManagerTurno.h"
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

#include "ArchivoPaciente.h"
#include "ArchivoTurno.h"
#include "ArchivoMedico.h"
#include "ArchivoMedicoEspecialidad.h"
#include "ArchivoEspecialidad.h"
#include "Paciente.h"
#include "Turnos.h"
#include "Medico.h"
#include "MedicoEspecialidad.h"
#include "Especialidad.h"
#include "Fecha.h"
#include "Hora.h"

using namespace std;

void ManagerTurno::sacarTurno() {
    ArchivoPaciente archivoPaciente("paciente.dat");
    ArchivoTurno archivoTurno("turnos.dat");
    ArchivoMedico archivoMedico("medicos.dat");
    ArchivoMedicoEspecialidad archivoMedEsp("medicoespecialidades.dat");
    ArchivoEspecialidad archivoEspecialidad("especialidad.dat");

    string dni;
    int posPaciente = -1;
   do {
    cout << "Ingrese DNI del paciente: ";
    cin >> dni;

    posPaciente = archivoPaciente.BuscarPorDni(dni);
    if (posPaciente == -1) {
        cout << "Paciente no encontrado. Intente nuevamente o ingrese 0 para cancelar.\n";
        if (dni == "0") return;
    }

} while (posPaciente == -1);

Paciente paciente = archivoPaciente.Leer(posPaciente);

// Mostrar paciente en tabla
cout << "\n================================== DATOS DEL PACIENTE ==================================\n";
cout << left << setw(5) << "ID"
     << setw(12) << "DNI"
     << setw(15) << "Nombre"
     << setw(15) << "Apellido"
     << setw(15) << "Telefono"
     << setw(25) << "Email"
     << setw(12) << "ID Prestador"
     << endl;

cout << left << setw(5) << paciente.get_id()
     << setw(12) << paciente.get_dni()
     << setw(15) << paciente.get_nombre()
     << setw(15) << paciente.get_apellido()
     << setw(15) << paciente.get_telefono()
     << setw(25) << paciente.get_email()
     << setw(12) << paciente.get_idPrestador()
     << endl;

cout << "=========================================================================================\n";

    // Mostrar especialidades disponibles
    int cantEsp = archivoEspecialidad.cantidadRegistros();
    cout << "\nEspecialidades disponibles:\n";
    for (int i = 0; i < cantEsp; ++i) {
        Especialidad esp = archivoEspecialidad.leer(i);
        cout << "ID: " << esp.get_id()
             << " - " << esp.get_nombreEspecialidad() << endl;
    }

    // Elegir especialidad
    int idEspecialidad;
    cout << "\nSeleccione el ID de la especialidad deseada: ";
    cin >> idEspecialidad;

    // Mostrar médicos que tienen esa especialidad
    int cantidad = archivoMedEsp.CantidadRegistros();
    bool hayMedicos = false;

    cout << "\nMédicos con la especialidad seleccionada:\n";

    for (int i = 0; i < cantidad; ++i) {
        MedicoEspecialidad medEsp = archivoMedEsp.Leer(i);

        if (medEsp.getIdEspecialidad() == idEspecialidad) {
            int posMedico = archivoMedico.Buscar(medEsp.getIdMedico());
            if (posMedico == -1) continue;

            Medico medico = archivoMedico.Leer(posMedico);

            cout << "ID MedicoEspecialidad: " << medEsp.getId() << endl;
            cout << "  - Nombre: " << medico.get_nombre() << " " << medico.get_apellido() << endl;
            cout << "  - Matrícula: " << medico.get_matricula() << endl;
            cout << "---------------------------" << endl;

            hayMedicos = true;
        }
    }

    if (!hayMedicos) {
        cout << "No hay médicos disponibles para esa especialidad." << endl;
        return;
    }

    // Selección de médico
    int idMedicoEspecialidad;
    cout << "\nIngrese el ID MédicoEspecialidad con el que desea sacar turno: ";
    cin >> idMedicoEspecialidad;

    // Validar ID MédicoEspecialidad
    bool idValido = false;
    for (int i = 0; i < cantidad; ++i) {
        MedicoEspecialidad medEsp = archivoMedEsp.Leer(i);
        if (medEsp.getId() == idMedicoEspecialidad && medEsp.getIdEspecialidad() == idEspecialidad) {
            idValido = true;
            break;
        }
    }
    if (!idValido) {
        cout << "El ID de MédicoEspecialidad ingresado no es válido para esta especialidad." << endl;
        return;
    }

    // Ingresar fecha
    string inputFecha;
    int dia, mes, anio;

    while (true) {
        cout << "\nIngrese la fecha del turno (formato DD/MM/AAAA): ";
        cin >> inputFecha;
        if (sscanf(inputFecha.c_str(), "%d/%d/%d", &dia, &mes, &anio) == 3) break;
        cout << "Formato inválido. Ejemplo válido: 15/08/2025" << endl;
    }

    Fecha fechaTurno(dia, mes, anio);

    // Mostrar agenda
    cout << "\nAgenda disponible para el día "
         << dia << "/" << mes << "/" << anio << ":\n";

    vector<Hora> agendaDisponible;

    int totalTurnos = archivoTurno.CantidadRegistros();
    for (int h = 8; h < 16; ++h) {
        for (int m = 0; m < 60; m += 20) {
            Hora hora(h, m);
            bool ocupado = false;

            for (int pos = 0; pos < totalTurnos; ++pos) {
                Turno t = archivoTurno.Leer(pos);
                if (
                    t.getIdMedicoEspecialidad() == idMedicoEspecialidad &&
                    t.getFechaAtencion() == fechaTurno &&
                    t.getHoraAtencion() == hora
                ) {
                    ocupado = true;
                    break;
                }
            }
            if (!ocupado) {
                agendaDisponible.push_back(hora);
                cout << " - " << hora.toString() << endl;
            }
        }
    }

    if (agendaDisponible.empty()) {
        cout << "No hay horarios disponibles para esa fecha." << endl;
        return;
    }

    // Selección de hora válida
    string inputHora;
    int horaSel, minSel;
    Hora horaTurno;
    bool esValida = false;

    do {
        cout << "\nIngrese el horario del turno (formato HH:MM): ";
        cin >> inputHora;

        if (sscanf(inputHora.c_str(), "%d:%d", &horaSel, &minSel) != 2) {
            cout << "Formato inválido. Ejemplo válido: 14:20\n";
            continue;
        }

        if (horaSel < 8 || horaSel > 15 || (minSel != 0 && minSel != 20 && minSel != 40)) {
            cout << "Horario fuera del rango permitido. Intente nuevamente." << endl;
            continue;
        }

        horaTurno = Hora(horaSel, minSel);
        esValida = false;

        for (const Hora& h : agendaDisponible) {
            if (h == horaTurno) {
                esValida = true;
                break;
            }
        }

        if (!esValida) {
            cout << "Ese horario ya está ocupado. Intente otro." << endl;
        }

    } while (!esValida);

    // Crear y guardar turno
    Turno nuevoTurno;
    nuevoTurno.setId(archivoTurno.CantidadRegistros() + 1);
    nuevoTurno.setIdPaciente(paciente.get_id());
    nuevoTurno.setIdMedicoEspecialidad(idMedicoEspecialidad);
    nuevoTurno.setFechaAtencion(fechaTurno);
    nuevoTurno.setHoraAtencion(horaTurno);
    nuevoTurno.setImporteConsulta(3500.0f);
    nuevoTurno.setCancelado(false);
    nuevoTurno.setSobreturno(false);
    nuevoTurno.setDuracionTurno(Hora(0, 20));

    if (archivoTurno.Guardar(nuevoTurno)) {
        cout << "Turno registrado correctamente." << endl;
    } else {
        cout << "Error al guardar el turno." << endl;
    }
}


void ManagerTurno::mostrarAgendaSemanal() {

    ArchivoEspecialidad archivoEspecialidad("especialidad.dat");
    ArchivoMedico archivoMedico("medicos.dat");
    ArchivoMedicoEspecialidad archivoMedEsp("medicoespecialidades.dat");
    ArchivoTurno archivoTurno("turnos.dat");
    ArchivoPaciente archivoPaciente("paciente.dat");

    // 1. Mostrar especialidades
    int cantEsp = archivoEspecialidad.cantidadRegistros();
    cout << "\nEspecialidades disponibles:\n";
    for (int i = 0; i < cantEsp; ++i) {
        Especialidad esp = archivoEspecialidad.leer(i);
        cout << "ID: " << esp.get_id() << " - " << esp.get_nombreEspecialidad() << endl;
    }

    // 2. Pedir especialidad
    int idEspecialidad;
    cout << "\nIngrese el ID de la especialidad: ";
    cin >> idEspecialidad;

    // 3. Mostrar medicos con esa especialidad
    int cantMedEsp = archivoMedEsp.CantidadRegistros();
    bool hayMedicos = false;

    cout << "\nMedicos con esa especialidad:\n";
    for (int i = 0; i < cantMedEsp; ++i) {
        MedicoEspecialidad medEsp = archivoMedEsp.Leer(i);
        if (medEsp.getIdEspecialidad() == idEspecialidad) {
            int posMed = archivoMedico.Buscar(medEsp.getIdMedico());
            if (posMed != -1) {
                Medico med = archivoMedico.Leer(posMed);
                cout << "ID MedicoEspecialidad: " << medEsp.getId() << endl;
                cout << "  - " << med.get_nombre() << " " << med.get_apellido()
                     << " | Matricula: " << med.get_matricula() << endl;
                hayMedicos = true;
            }
        }
    }

    if (!hayMedicos) {
        cout << "No hay medicos para esa especialidad.\n";
        return;
    }

    // 4. Seleccionar MedicoEspecialidad
    int idMedicoEspecialidad;
    cout << "\nIngrese el ID MedicoEspecialidad para ver su agenda: ";
    cin >> idMedicoEspecialidad;

    // 5. Pedir fecha de inicio de la semana (Lunes)
    int dia, mes, anio;
    cout << "\nIngrese la fecha de inicio de semana (Lunes):\n";
    cout << "  Dia: "; cin >> dia;
    cout << "  Mes: "; cin >> mes;
    cout << "  Anio: "; cin >> anio;
    Fecha fechaLunes(dia, mes, anio);

    // 6. Mostrar agenda semanal (Lunes a Viernes)
    cout << "\nAgenda semanal para medico ID: " << idMedicoEspecialidad << endl;

    for (int d = 0; d < 5; ++d) {
        Fecha fechaDia = fechaLunes;
        fechaDia.sumarDias(d);

        cout << "\n" << fechaDia.toString() << endl;
        cout << "-------------------------------" << endl;

        for (int h = 8; h < 16; ++h) {
            for (int m = 0; m < 60; m += 20) {
                Hora hora(h, m);
                bool ocupado = false;
                Turno turno;
                int pos = 0;

                int cantidadTurnos = archivoTurno.CantidadRegistros();

                for (int pos = 0; pos < cantidadTurnos; ++pos) {
                    Turno turno = archivoTurno.Leer(pos);
                    if (
                        turno.getIdMedicoEspecialidad() == idMedicoEspecialidad &&
                        turno.getFechaAtencion() == fechaDia &&
                        turno.getHoraAtencion() == hora
                    ) {
                        ocupado = true;
                        int idPaciente = turno.getIdPaciente();
                        int posPac = archivoPaciente.Buscar(idPaciente);
                        if (posPac != -1) {
                            Paciente paciente = archivoPaciente.Leer(posPac);
                            cout << hora.toString() << " - OCUPADO - "
                                 << paciente.get_nombre() << " " << paciente.get_apellido()
                                 << " | Tel: " << paciente.get_telefono() << endl;
                        } else {
                            cout << hora.toString() << " - OCUPADO - Paciente desconocido (ID: "
                                 << idPaciente << ")" << endl;
                        }
                        break;
                    }
                }

                if (!ocupado) {
                    cout << hora.toString() << " - LIBRE" << endl;
                }
            }
        }
    }

    cout << "\nFin de la agenda semanal." << endl;
}

void ManagerTurno::listarTurnos() {
    ArchivoTurno archivo("turnos.dat");

    cout << "\n============= LISTADO DE TURNOS =============\n";
    archivo.ListarTurnos();
    cout << "=============================================\n";
}

