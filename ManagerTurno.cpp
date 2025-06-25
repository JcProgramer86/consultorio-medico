#include "ManagerTurno.h"
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>

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
#include "ArchivoPrestador.h"
#include "Menu.h"
#include "Fecha.h"
#include "Hora.h"

using namespace std;
extern Menu menu;

void ManagerTurno::sacarTurno() {
    system("cls");
    menu.menuHeader();
    cout << "===============================================" << endl;
    cout << "                SACAR NUEVO TURNO              " << endl;
    cout << "===============================================" << endl;

    ArchivoPaciente archivoPaciente("paciente.dat");
    ArchivoTurno archivoTurno("turnos.dat");
    ArchivoMedico archivoMedico("medicos.dat");
    ArchivoMedicoEspecialidad archivoMedEsp("medicoespecialidades.dat");
    ArchivoEspecialidad archivoEspecialidad("especialidad.dat");
    ArchivoPrestador archivoPrestador("prestadores.dat");

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

    // Obtener nombre del prestador
    string nombrePrestador = "Desconocido";
    int posPrestador = archivoPrestador.Buscar(paciente.get_idPrestador());
    if (posPrestador >= 0) {
        Prestador prestador = archivoPrestador.Leer(posPrestador);
        nombrePrestador = prestador.getNombrePrestador();
    }

    // Mostrar paciente en tabla
    cout << "\n================================== DATOS DEL PACIENTE ==================================\n";
    cout << left << setw(5) << "ID"
         << setw(12) << "DNI"
         << setw(15) << "Nombre"
         << setw(15) << "Apellido"
         << setw(15) << "Telefono"
         << setw(25) << "Email"
         << setw(20) << "Prestador"
         << endl;

    cout << left << setw(5) << paciente.get_id()
         << setw(12) << paciente.get_dni()
         << setw(15) << paciente.get_nombre()
         << setw(15) << paciente.get_apellido()
         << setw(15) << paciente.get_telefono()
         << setw(25) << paciente.get_email()
         << setw(20) << nombrePrestador
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

    int idEspecialidad;
    cout << "\nSeleccione el ID de la especialidad deseada: ";
    cin >> idEspecialidad;

    // Mostrar medicos de esa especialidad
    int cantidad = archivoMedEsp.CantidadRegistros();
    bool hayMedicos = false;

    cout << "\nMedicos con la especialidad seleccionada:\n";
    for (int i = 0; i < cantidad; ++i) {
        MedicoEspecialidad medEsp = archivoMedEsp.Leer(i);
        if (medEsp.getIdEspecialidad() == idEspecialidad) {
            int posMedico = archivoMedico.Buscar(medEsp.getIdMedico());
            if (posMedico == -1) continue;

            Medico medico = archivoMedico.Leer(posMedico);

            cout << "ID MedicoEspecialidad: " << medEsp.getId() << endl;
            cout << "  - Nombre: " << medico.get_nombre() << " " << medico.get_apellido() << endl;
            cout << "  - Matricula: " << medico.get_matricula() << endl;
            cout << "---------------------------" << endl;

            hayMedicos = true;
        }
    }

    if (!hayMedicos) {
        cout << "No hay medicos disponibles para esa especialidad." << endl;
        return;
    }

    int idMedicoEspecialidad;
    cout << "\nIngrese el ID MedicoEspecialidad con el que desea sacar turno: ";
    cin >> idMedicoEspecialidad;

    bool idValido = false;
    for (int i = 0; i < cantidad; ++i) {
        MedicoEspecialidad medEsp = archivoMedEsp.Leer(i);
        if (medEsp.getId() == idMedicoEspecialidad && medEsp.getIdEspecialidad() == idEspecialidad) {
            idValido = true;
            break;
        }
    }
    if (!idValido) {
        cout << "El ID de MedicoEspecialidad ingresado no es valido para esta especialidad." << endl;
        return;
    }

    cin.ignore(); // Limpiar buffer
    Fecha fechaTurno = Fecha::leerFechaValida("\nIngrese la fecha del turno (formato DD/MM/AAAA): ", false, true);

    cout << "\nAgenda disponible para el dia " << fechaTurno.toString() << ":\n";

    vector<Hora> agendaDisponible;
    int totalTurnos = archivoTurno.CantidadRegistros();
    for (int h = 8; h < 16; ++h) {
        for (int m = 0; m < 60; m += 20) {
            Hora hora(h, m);
            bool ocupado = false;

            for (int pos = 0; pos < totalTurnos; ++pos) {
                Turno t = archivoTurno.Leer(pos);
                if (t.getIdMedicoEspecialidad() == idMedicoEspecialidad && t.getFechaAtencion() == fechaTurno && t.getHoraAtencion() == hora) {
                    ocupado = true;
                    break;
                }
            }

            cout << " - " << hora.toString();
            if (ocupado) cout << " (OCUPADO)";
            else agendaDisponible.push_back(hora);
            cout << endl;
        }
    }

    if (agendaDisponible.empty()) {
        cout << "No hay horarios disponibles para esa fecha." << endl;
        return;
    }

    string inputHora;
    int horaSel, minSel;
    Hora horaTurno;
    bool esValida = false;

    do {
        cout << "\nIngrese el horario del turno (formato HH:MM): ";
        cin >> inputHora;

        if (sscanf(inputHora.c_str(), "%d:%d", &horaSel, &minSel) != 2) {
            cout << "Formato invalido. Ejemplo valido: 14:20\n";
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
            cout << "Ese horario ya esta ocupado o no es valido. Intente otro." << endl;
        }

    } while (!esValida);

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
        cout << "\nTurno registrado correctamente." << endl;
        cout << "===================================" << endl;
        cout << "ID Turno: " << nuevoTurno.getId() << endl;
        cout << "Paciente ID: " << nuevoTurno.getIdPaciente() << endl;
        cout << "MedicoEspecialidad ID: " << nuevoTurno.getIdMedicoEspecialidad() << endl;
        cout << "Fecha: " << nuevoTurno.getFechaAtencion().toString() << endl;
        cout << "Hora: " << nuevoTurno.getHoraAtencion().toString() << endl;
        cout << "Importe: $" << nuevoTurno.getImporteConsulta() << endl;
        cout << "Duracion: " << nuevoTurno.getDuracionTurno().toString() << " minutos" << endl;
        cout << "===================================" << endl;
    } else {
        cout << "Error al guardar el turno." << endl;
    }
    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
}




void ManagerTurno::mostrarAgendaSemanal() {
    system("cls");
    menu.menuHeader();
    cout << "===============================================" << endl;
    cout << "           CONSULTA DE AGENDA SEMANAL          " << endl;
    cout << "===============================================" << endl;

    ArchivoEspecialidad archivoEspecialidad("especialidad.dat");
    ArchivoMedico archivoMedico("medicos.dat");
    ArchivoMedicoEspecialidad archivoMedEsp("medicoespecialidades.dat");
    ArchivoTurno archivoTurno("turnos.dat");
    ArchivoPaciente archivoPaciente("paciente.dat");

    // 1. Mostrar especialidades
    int cantEsp = archivoEspecialidad.cantidadRegistros();
    cout << "\nEspecialidades disponibles:\n";
    cout << left << setw(6) << "ID" << setw(30) << "Especialidad" << endl;
    cout << string(36, '-') << endl;
    for (int i = 0; i < cantEsp; ++i) {
        Especialidad esp = archivoEspecialidad.leer(i);
        cout << left << setw(6) << esp.get_id()
             << setw(30) << esp.get_nombreEspecialidad() << endl;
    }

    // 2. Pedir especialidad con validacion
    int idEspecialidad;
    bool idEspValido = false;
    do {
        cout << "\nIngrese el ID de la especialidad: ";
        cin >> idEspecialidad;
        for (int i = 0; i < cantEsp; ++i) {
            Especialidad esp = archivoEspecialidad.leer(i);
            if (esp.get_id() == idEspecialidad) {
                idEspValido = true;
                break;
            }
        }
        if (!idEspValido) cout << "ID de especialidad invalido. Intente nuevamente.\n";
    } while (!idEspValido);

    // 3. Mostrar medicos con esa especialidad (tabla)
    int cantMedEsp = archivoMedEsp.CantidadRegistros();
    vector<MedicoEspecialidad> medicosDeEspecialidad;
    vector<Medico> medicosInfo;

    for (int i = 0; i < cantMedEsp; ++i) {
        MedicoEspecialidad medEsp = archivoMedEsp.Leer(i);
        if (medEsp.getIdEspecialidad() == idEspecialidad) {
            int posMed = archivoMedico.Buscar(medEsp.getIdMedico());
            if (posMed != -1) {
                Medico med = archivoMedico.Leer(posMed);
                medicosDeEspecialidad.push_back(medEsp);
                medicosInfo.push_back(med);
            }
        }
    }

    if (medicosDeEspecialidad.empty()) {
        cout << "\nNo hay medicos para esa especialidad.\n";
        cout << "\nPresione Enter para volver al menu...";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "\nMedicos con esa especialidad:\n";
    cout << left
         << setw(8) << "ID-M/E"
         << setw(25) << "Nombre"
         << setw(15) << "Matricula"
         << endl;
    cout << string(48, '-') << endl;

    for (size_t i = 0; i < medicosDeEspecialidad.size(); ++i) {
        cout << left
             << setw(8) << medicosDeEspecialidad[i].getId()
             << setw(25) << (medicosInfo[i].get_nombre() + " " + medicosInfo[i].get_apellido())
             << setw(15) << medicosInfo[i].get_matricula()
             << endl;
    }

    // 4. Seleccionar MedicoEspecialidad con validacion
    int idMedicoEspecialidad;
    int indiceMedicoElegido = -1;
    do {
        cout << "\nIngrese el ID MedicoEspecialidad para ver su agenda: ";
        cin >> idMedicoEspecialidad;
        for (size_t i = 0; i < medicosDeEspecialidad.size(); ++i) {
            if (medicosDeEspecialidad[i].getId() == idMedicoEspecialidad) {
                indiceMedicoElegido = i;
                break;
            }
        }
        if (indiceMedicoElegido == -1) {
            cout << "ID de MedicoEspecialidad invalido. Intente nuevamente.\n";
        }
    } while (indiceMedicoElegido == -1);

    // 5. Pedir fecha de inicio de la semana (Lunes) en formato dd/mm/aaaa
    string inputFecha;
    int dia, mes, anio;
    do {
        cout << "\nIngrese la fecha de inicio de semana (Lunes) (DD/MM/AAAA): ";
        cin >> inputFecha;
    } while (sscanf(inputFecha.c_str(), "%d/%d/%d", &dia, &mes, &anio) != 3);
    Fecha fechaLunes(dia, mes, anio);

    // 6. Mostrar agenda semanal (Lunes a Viernes) y NOMBRE del medico
    Medico medicoElegido = medicosInfo[indiceMedicoElegido];
    cout << "\nAgenda semanal para medico: "
         << medicoElegido.get_nombre() << " " << medicoElegido.get_apellido()
         << " (" << medicoElegido.get_matricula() << ")" << endl;

    for (int d = 0; d < 5; ++d) {
        Fecha fechaDia = fechaLunes;
        fechaDia.sumarDias(d);

        cout << "\n" << fechaDia.toString() << endl;
        cout << "-------------------------------" << endl;

        for (int h = 8; h < 16; ++h) {
            for (int m = 0; m < 60; m += 20) {
                Hora hora(h, m);
                bool ocupado = false;
                int idPaciente = -1;

                int cantidadTurnos = archivoTurno.CantidadRegistros();

                for (int pos = 0; pos < cantidadTurnos; ++pos) {
                    Turno turno = archivoTurno.Leer(pos);
                    if (
                        turno.getIdMedicoEspecialidad() == idMedicoEspecialidad &&
                        turno.getFechaAtencion() == fechaDia &&
                        turno.getHoraAtencion() == hora
                    ) {
                        ocupado = true;
                        idPaciente = turno.getIdPaciente();
                        int posPac = archivoPaciente.Buscar(idPaciente);
                        if (posPac != -1) {
                            Paciente paciente = archivoPaciente.Leer(posPac);
                            cout << setw(8) << hora.toString() << " - OCUPADO - "
                                 << setw(20) << (paciente.get_nombre() + " " + paciente.get_apellido())
                                 << " | Tel: " << paciente.get_telefono() << endl;
                        } else {
                            cout << setw(8) << hora.toString() << " - OCUPADO - Paciente desconocido (ID: "
                                 << idPaciente << ")" << endl;
                        }
                        break;
                    }
                }

                if (!ocupado) {
                    cout << setw(8) << hora.toString() << " - LIBRE" << endl;
                }
            }
        }
    }

    cout << "\nFin de la agenda semanal." << endl;
    cout << "\nPresione Enter para volver al menu...";
    cin.ignore();
    cin.get();
}


void ManagerTurno::listarTurnosPorPaciente() {

    system("cls");
    menu.menuHeader();
    cout << "===============================================" << endl;
    cout << "          TURNOS POR PACIENTE                  " << endl;
    cout << "===============================================" << endl;

    ArchivoPaciente archivoPaciente("paciente.dat");
    ArchivoTurno archivoTurno("turnos.dat");

    string dni;
    cout << "\nIngrese el DNI del paciente: ";
    cin >> dni;

    int posPac = archivoPaciente.BuscarPorDni(dni);
    if (posPac == -1) {
        cout << "Paciente no encontrado.\n";
        cout << "\nPresione Enter para continuar...";
        cin.ignore();
        cin.get();
        return;
    }

    Paciente paciente = archivoPaciente.Leer(posPac);
    cout << "\nTurnos del paciente: " << paciente.get_nombre() << " " << paciente.get_apellido() << "\n";

    int totalTurnos = archivoTurno.CantidadRegistros();
    bool hayTurnos = false;

    for (int i = 0; i < totalTurnos; i++) {
        Turno t = archivoTurno.Leer(i);
        if (t.getIdPaciente() == paciente.get_id()) {
            mostrarTurnoResumen(t); // Reemplazado
            hayTurnos = true;
        }
    }

    if (!hayTurnos) {
        cout << "Este paciente no tiene turnos registrados.\n";
    }

    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
}


void ManagerTurno::listarTurnosPorDia() {

    system("cls");
    menu.menuHeader();
    cout << "===============================================" << endl;
    cout << "             TURNOS POR DIA                    " << endl;
    cout << "===============================================" << endl;

    string inputFecha;
    int d, m, a;

    // Nueva forma de ingreso: dd/mm/aaaa
    do {
        cout << "\nIngrese la fecha (DD/MM/AAAA): ";
        cin >> inputFecha;
    } while (sscanf(inputFecha.c_str(), "%d/%d/%d", &d, &m, &a) != 3);

    Fecha fecha(d, m, a);

    ArchivoTurno archivoTurno("turnos.dat");
    int total = archivoTurno.CantidadRegistros();
    bool hay = false;

    for (int i = 0; i < total; i++) {
        Turno t = archivoTurno.Leer(i);
        if (t.getFechaAtencion() == fecha) {
            mostrarTurnoResumen(t);  // Reemplazado
            hay = true;
        }
    }

    if (!hay) cout << "No hay turnos para ese dia.\n";

    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
}



void ManagerTurno::listarTurnosPorSemana() {
    system("cls");
    menu.menuHeader();
    cout << "===============================================" << endl;
    cout << "            TURNOS POR SEMANA                  " << endl;
    cout << "===============================================" << endl;

    string inputFecha;
    int d, m, a;

    do {
        cout << "\nIngrese el LUNES de la semana (DD/MM/AAAA): ";
        cin >> inputFecha;
    } while (sscanf(inputFecha.c_str(), "%d/%d/%d", &d, &m, &a) != 3);

    Fecha lunes(d, m, a);

    ArchivoTurno archivoTurno("turnos.dat");
    int total = archivoTurno.CantidadRegistros();
    bool hay = false;

    for (int i = 0; i < 5; i++) {
        Fecha dia = lunes;
        dia.sumarDias(i);
        cout << "\n--- Turnos del " << dia.toString() << " ---\n";

        for (int j = 0; j < total; j++) {
            Turno t = archivoTurno.Leer(j);
            if (t.getFechaAtencion() == dia) {
                mostrarTurnoResumen(t);
                hay = true;
            }
        }
    }

    if (!hay) {
        cout << "No hay turnos para esa semana.\n";
    }

    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
}


void ManagerTurno::listarTurnosPorMes() {
    system("cls");
    menu.menuHeader();
    cout << "===============================================" << endl;
    cout << "            TURNOS POR MES                     " << endl;
    cout << "===============================================" << endl;

    string inputFecha;
    int mes, anio;

    do {
        cout << "\nIngrese el mes y anio (MM/AAAA): ";
        cin >> inputFecha;
    } while (sscanf(inputFecha.c_str(), "%d/%d", &mes, &anio) != 2);

    ArchivoTurno archivoTurno("turnos.dat");
    int total = archivoTurno.CantidadRegistros();
    bool hay = false;

    // Primero, traemos todos los turnos de ese mes en un vector y los ordenamos por fecha
    vector<Turno> turnosDelMes;
    for (int i = 0; i < total; i++) {
        Turno t = archivoTurno.Leer(i);
        Fecha f = t.getFechaAtencion();
        if (f.getMes() == mes && f.getAnio() == anio) {
            turnosDelMes.push_back(t);
            hay = true;
        }
    }

    if (!hay) {
        cout << "No hay turnos en ese mes.\n";
    } else {
        // Ordena los turnos por fecha y hora
        sort(turnosDelMes.begin(), turnosDelMes.end(), [](const Turno& a, const Turno& b) {
            Fecha fa = a.getFechaAtencion(), fb = b.getFechaAtencion();
            if (fa.getAnio() != fb.getAnio()) return fa.getAnio() < fb.getAnio();
            if (fa.getMes() != fb.getMes()) return fa.getMes() < fb.getMes();
            if (fa.getDia() != fb.getDia()) return fa.getDia() < fb.getDia();
            // Si es el mismo día, ordenar por hora
            if (a.getHoraAtencion().getHora() != b.getHoraAtencion().getHora())
                return a.getHoraAtencion().getHora() < b.getHoraAtencion().getHora();
            return a.getHoraAtencion().getMinuto() < b.getHoraAtencion().getMinuto();
        });

        // Mostrar separador de día
        int ultimoDia = -1;
        for (const Turno& t : turnosDelMes) {
            Fecha f = t.getFechaAtencion();
            if (f.getDia() != ultimoDia) {
                ultimoDia = f.getDia();
                cout << "\n====================================\n";
                cout << "   Turnos del dia: " << f.toString() << endl;
                cout << "====================================\n";
            }
            mostrarTurnoResumen(t);
        }
    }

    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
}





void ManagerTurno::mostrarTurnoResumen(Turno turno) {
    ArchivoPaciente archivoPaciente("paciente.dat");
    ArchivoMedicoEspecialidad archivoMedicoEspecialidad("medicoespecialidades.dat");
    ArchivoMedico archivoMedico("medicos.dat");
    ArchivoEspecialidad archivoEspecialidad("especialidad.dat");

    Paciente paciente = archivoPaciente.Leer(archivoPaciente.Buscar(turno.getIdPaciente()));
    MedicoEspecialidad medEsp = archivoMedicoEspecialidad.Leer(
        archivoMedicoEspecialidad.Buscar(turno.getIdMedicoEspecialidad()));
    Medico medico = archivoMedico.Leer(archivoMedico.Buscar(medEsp.getIdMedico()));

    // --- Agregado: obtener la especialidad ---
    int posEsp = archivoEspecialidad.buscarPorId(medEsp.getIdEspecialidad());
    Especialidad especialidad;
    if (posEsp != -1) {
        especialidad = archivoEspecialidad.leer(posEsp);
    }

    cout << "\n========= RESUMEN DE TURNO =========" << endl;
    cout << "Paciente: " << paciente.get_nombre() << " " << paciente.get_apellido() << endl;
    cout << "Medico: " << medico.get_nombre() << " " << medico.get_apellido() << endl;
    cout << "Especialidad: ";
    if (posEsp != -1) cout << especialidad.get_nombreEspecialidad() << endl;
    else cout << "No encontrada" << endl;
    cout << "Fecha: " << turno.getFechaAtencion().toString() << endl;
    cout << "Hora: " << turno.getHoraAtencion().toString() << endl;
    cout << "Importe: $" << fixed << setprecision(2) << turno.getImporteConsulta() << endl;
    cout << "====================================" << endl;
}


void ManagerTurno::mostrarTurnoDetalle(Turno turno) {
    ArchivoPaciente archivoPaciente("paciente.dat");
    ArchivoMedicoEspecialidad archivoMedicoEspecialidad("medicoespecialidades.dat");
    ArchivoMedico archivoMedico("medicos.dat");
    ArchivoEspecialidad archivoEspecialidad("especialidad.dat");
    ArchivoPrestador archivoPrestador("prestadores.dat");

    Paciente paciente = archivoPaciente.Leer(archivoPaciente.Buscar(turno.getIdPaciente()));
    MedicoEspecialidad medEsp = archivoMedicoEspecialidad.Leer(
        archivoMedicoEspecialidad.Buscar(turno.getIdMedicoEspecialidad()));
    Medico medico = archivoMedico.Leer(archivoMedico.Buscar(medEsp.getIdMedico()));
    Especialidad especialidad = archivoEspecialidad.leer(archivoEspecialidad.buscarPorId(medEsp.getIdEspecialidad()));
    Prestador prestador = archivoPrestador.Leer(archivoPrestador.Buscar(paciente.get_idPrestador()));

    cout << "\n=========== DETALLE COMPLETO DEL TURNO ===========" << endl;
    cout << left;
    cout << setw(20) << "ID Turno:" << turno.getId() << endl;
    cout << setw(20) << "Paciente:" << paciente.get_nombre() << " " << paciente.get_apellido() << endl;
    cout << setw(20) << "DNI:" << paciente.get_dni() << endl;
    cout << setw(20) << "Prestador:" << prestador.getNombrePrestador() << endl;
    cout << setw(20) << "Especialidad:" << especialidad.get_nombreEspecialidad() << endl;
    cout << setw(20) << "Medico:" << medico.get_nombre() << " " << medico.get_apellido() << endl;
    cout << setw(20) << "Matricula:" << medico.get_matricula() << endl;
    cout << setw(20) << "Fecha:" << turno.getFechaAtencion().toString() << endl;
    cout << setw(20) << "Hora:" << turno.getHoraAtencion().toString() << endl;
    cout << setw(20) << "Importe:" << "$" << fixed << setprecision(2) << turno.getImporteConsulta() << endl;
    cout << setw(20) << "Duracion:" << turno.getDuracionTurno().toString() << " minutos" << endl;
    cout << setw(20) << "Sobreturno:" << (turno.getSobreturno() ? "SI" : "NO") << endl;
    cout << setw(20) << "Asistio:" << (turno.getAsistio() ? "SI" : "NO") << endl;
    cout << setw(20) << "Cancelado:" << (turno.getCancelado() ? "SI" : "NO") << endl;
    cout << setw(20) << "Observaciones:" << turno.getObservaciones() << endl;
    cout << "===================================================" << endl;
}



