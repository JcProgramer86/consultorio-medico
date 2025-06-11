#include "ManagerTurno.h"

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
    ArchivoMedico archivoMedico("medico.dat");
    ArchivoMedicoEspecialidad archivoMedEsp("medico_especialidad.dat");
    ArchivoEspecialidad archivoEspecialidad("especialidad.dat");

    string dni;
    cout << "Ingrese DNI del paciente: ";
    cin >> dni;

    int posPaciente = archivoPaciente.BuscarPorDni(dni);
    if (posPaciente == -1) {
        cout << "Paciente no encontrado." << endl;
        return;
    }
    Paciente paciente = archivoPaciente.Leer(posPaciente);

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
        cout << "⚠️ No hay médicos para esa especialidad." << endl;
        return;
    }

    // Selección de médico
    int idMedicoEspecialidad;
    cout << "\nIngrese el ID MédicoEspecialidad con el que desea sacar turno: ";
    cin >> idMedicoEspecialidad;

    // Ingresar fecha
    int dia, mes, anio;
    cout << "\nIngrese la fecha del turno:" << endl;
    cout << "  Día: "; cin >> dia;
    cout << "  Mes: "; cin >> mes;
    cout << "  Año: "; cin >> anio;

    Fecha fechaTurno(dia, mes, anio);

    // Mostrar agenda de 8:00 a 16:00 con turnos cada 20 minutos
    cout << "\nAgenda disponible para el día "
         << dia << "/" << mes << "/" << anio << ":\n";

    vector<Hora> agendaDisponible;

    for (int h = 8; h < 16; ++h) {
        for (int m = 0; m < 60; m += 20) {
            Hora hora(h, m);
            bool ocupado = false;

            Turno t;
            int totalTurnos = archivoTurno.CantidadRegistros();
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
                cout << " - " << hora.toString() << endl; // asegurate de tener este método en Hora
            }
        }
    }

    if (agendaDisponible.empty()) {
        cout << "⚠️ No hay horarios disponibles para esa fecha." << endl;
        return;
    }

    // Selección de hora
    int horaSel, minSel;
    cout << "\nSeleccione la hora (formato 24h): "; cin >> horaSel;
    cout << "Minutos (0, 20, 40): "; cin >> minSel;

    if (minSel % 20 != 0) {
        cout << "❌ Minutos inválidos. Deben ser múltiplos de 20." << endl;
        return;
    }

    Hora horaTurno(horaSel, minSel);
    bool esValida = false;
    for (const Hora& h : agendaDisponible) {
        if (h == horaTurno) {
            esValida = true;
            break;
        }
    }

    if (!esValida) {
        cout << "❌ Ese horario ya está ocupado o fuera del rango permitido." << endl;
        return;
    }

    // Crear y guardar turno
    Turno nuevoTurno;
    nuevoTurno.setId(archivoTurno.CantidadRegistros() + 1); // setId, NO setIdTurno
    nuevoTurno.setIdPaciente(paciente.get_id());
    nuevoTurno.setIdMedicoEspecialidad(idMedicoEspecialidad);
    nuevoTurno.setFechaAtencion(fechaTurno); // setFechaAtencion, NO setFechaTurno
    nuevoTurno.setHoraAtencion(horaTurno);   // setHoraAtencion, NO setHoraTurno
    nuevoTurno.setImporteConsulta(3500.0f); // puede venir de config
    nuevoTurno.setCancelado(false);
    nuevoTurno.setSobreturno(false);
    nuevoTurno.setDuracionTurno(Hora(0, 20));

    if (archivoTurno.Guardar(nuevoTurno)) {
        cout << "✅ Turno registrado correctamente." << endl;
    } else {
        cout << "❌ Error al guardar el turno." << endl;
    }
}

void ManagerTurno::mostrarAgendaSemanal() {

    ArchivoEspecialidad archivoEspecialidad("especialidad.dat");
    ArchivoMedico archivoMedico("medico.dat");
    ArchivoMedicoEspecialidad archivoMedEsp("medico_especialidad.dat");
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

    // 3. Mostrar médicos con esa especialidad
    int cantMedEsp = archivoMedEsp.CantidadRegistros();
    bool hayMedicos = false;

    cout << "\nMédicos con esa especialidad:\n";
    for (int i = 0; i < cantMedEsp; ++i) {
        MedicoEspecialidad medEsp = archivoMedEsp.Leer(i);
        if (medEsp.getIdEspecialidad() == idEspecialidad) {
            int posMed = archivoMedico.Buscar(medEsp.getIdMedico());
            if (posMed != -1) {
                Medico med = archivoMedico.Leer(posMed);
                cout << "ID MédicoEspecialidad: " << medEsp.getId() << endl;
                cout << "  - " << med.get_nombre() << " " << med.get_apellido()
                     << " | Matrícula: " << med.get_matricula() << endl;
                hayMedicos = true;
            }
        }
    }

    if (!hayMedicos) {
        cout << "⚠️ No hay médicos para esa especialidad.\n";
        return;
    }

    // 4. Seleccionar MédicoEspecialidad
    int idMedicoEspecialidad;
    cout << "\nIngrese el ID MédicoEspecialidad para ver su agenda: ";
    cin >> idMedicoEspecialidad;

    // 5. Pedir fecha de inicio de la semana (Lunes)
    int dia, mes, anio;
    cout << "\nIngrese la fecha de inicio de semana (Lunes):\n";
    cout << "  Día: "; cin >> dia;
    cout << "  Mes: "; cin >> mes;
    cout << "  Año: "; cin >> anio;
    Fecha fechaLunes(dia, mes, anio);

    // 6. Mostrar agenda semanal (Lunes a Viernes)
    cout << "\n🗓️ Agenda semanal para médico ID: " << idMedicoEspecialidad << endl;

    for (int d = 0; d < 5; ++d) {
        Fecha fechaDia = fechaLunes;
        fechaDia.sumarDias(d); // asegurate que tenés este método en Fecha

        cout << "\n📅 " << fechaDia.toString() << endl;
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
                            cout << hora.toString() << " - ❌ OCUPADO - "
                                 << paciente.get_nombre() << " " << paciente.get_apellido()
                                 << " | Tel: " << paciente.get_telefono() << endl;
                        } else {
                            cout << hora.toString() << " - ❌ OCUPADO - Paciente desconocido (ID: "
                                 << idPaciente << ")" << endl;
                        }
                        break;
                    }
                }

                if (!ocupado) {
                    cout << hora.toString() << " - ✅ LIBRE" << endl;
                }
            }
        }
    }

    cout << "\n✅ Fin de la agenda semanal." << endl;
}
