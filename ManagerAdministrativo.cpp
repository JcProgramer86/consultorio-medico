#include "ManagerAdministrativo.h"
#include "ArchivoTurno.h"
#include "ArchivoMedicoEspecialidad.h"
#include "ArchivoPaciente.h"
#include "ArchivoMedico.h"
#include "ArchivoEspecialidad.h"
#include "Especialidad.h"
#include "Fecha.h"
#include "Persona.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

ManagerAdministrativo::ManagerAdministrativo() {}


float ManagerAdministrativo::obtenerFacturacionDelMes() {
    system("cls");
    cout << "==============================================" << endl;
    cout << "         CONSULTA DE FACTURACION MENSUAL      " << endl;
    cout << "==============================================" << endl;

    // Limpiar el buffer antes de pedir la fecha
    cin.ignore();
    Fecha fecha = Fecha::leerMesAnioValido("Ingrese mes y anio (MM/AAAA): ");
    int mes = fecha.getMes();
    int anio = fecha.getAnio();

    ArchivoTurno archivo("turnos.dat");
    float total = 0;
    int cantidad = 0;

    for (int i = 0; i < archivo.CantidadRegistros(); i++) {
        Turno t = archivo.Leer(i);
        Fecha f = t.getFechaAtencion();
        if (f.getMes() == mes && f.getAnio() == anio && !t.getCancelado() && t.getAsistio()) {
            total += t.getImporteConsulta();
            cantidad++;
        }
    }

    cout << "\n----------------------------------------------" << endl;
    cout << "Mes consultado: " << (mes < 10 ? "0" : "") << mes << "/" << anio << endl;
    cout << "Turnos facturados: " << cantidad << endl;
    cout << "----------------------------------------------" << endl;

    cout << fixed << setprecision(2);

    if (cantidad > 0) {
        cout << "Facturacion total: $ " << total << endl;
    } else {
        cout << "No se registro facturacion para ese periodo." << endl;
    }

    cout << "----------------------------------------------" << endl;
    cout << "\nPresione Enter para volver al menu...";
    cin.ignore();
    cin.get();
    return total;
}

void ManagerAdministrativo::listarPacientesAtendidosPorEspecialidadYMes() {
    system("cls");
    cout << "==============================================" << endl;
    cout << "      PACIENTES ATENDIDOS POR ESPECIALIDAD    " << endl;
    cout << "==============================================" << endl;

    // Limpiar buffer por si venimos de un cin anterior
    cin.ignore();

    // Usar el método profesional de fecha por mes
    Fecha fecha = Fecha::leerMesAnioValido("Ingrese mes y anio (MM/AAAA): ");
    int mes = fecha.getMes();
    int anio = fecha.getAnio();

    // Mostrar especialidades disponibles
    ArchivoEspecialidad aEspecialidad("especialidad.dat");
    int cantEsp = aEspecialidad.cantidadRegistros();
    cout << "\nEspecialidades disponibles:\n";
    cout << left << setw(6) << "ID" << setw(30) << "Especialidad" << endl;
    cout << string(36, '-') << endl;
    for (int i = 0; i < cantEsp; ++i) {
        Especialidad esp = aEspecialidad.leer(i);
        cout << left << setw(6) << esp.get_id()
             << setw(30) << esp.get_nombreEspecialidad() << endl;
    }

    int idEsp;
    bool idValido = false;
    do {
        cout << "\nIngrese el ID de especialidad: ";
        cin >> idEsp;
        for (int i = 0; i < cantEsp; ++i) {
            if (aEspecialidad.leer(i).get_id() == idEsp) {
                idValido = true;
                break;
            }
        }
        if (!idValido) cout << "[!] ID de especialidad no valido. Intente nuevamente.\n";
    } while (!idValido);

    ArchivoTurno aTurno("turnos.dat");
    ArchivoMedicoEspecialidad aME("medicoespecialidades.dat");
    ArchivoPaciente aPaciente("paciente.dat");

    bool hayPacientes = false;
    cout << "\n==============================================" << endl;
    cout << "Pacientes atendidos en " << (mes < 10 ? "0" : "") << mes << "/" << anio
         << " para la especialidad: " << aEspecialidad.leer(idEsp-1).get_nombreEspecialidad() << endl;
    cout << "----------------------------------------------" << endl;

    for (int i = 0; i < aTurno.CantidadRegistros(); i++) {
        Turno t = aTurno.Leer(i);
        Fecha f = t.getFechaAtencion();
        if (f.getMes() == mes && f.getAnio() == anio && t.getAsistio() && !t.getCancelado()) {
            int posME = aME.Buscar(t.getIdMedicoEspecialidad());
            if (posME != -1) {
                MedicoEspecialidad me = aME.Leer(posME);
                if (me.getIdEspecialidad() == idEsp) {
                    int posPac = aPaciente.Buscar(t.getIdPaciente());
                    if (posPac != -1) {
                        Paciente p = aPaciente.Leer(posPac);
                        cout << "- " << p.get_nombre() << " " << p.get_apellido() << " (ID: " << p.get_id() << ")\n";
                        hayPacientes = true;
                    }
                }
            }
        }
    }

    if (!hayPacientes) {
        cout << "\nNo se encontraron pacientes atendidos en ese periodo para esa especialidad.\n";
    }

    cout << "----------------------------------------------" << endl;
    cout << "\nPresione Enter para volver al menu...";
    cin.ignore();
    cin.get();
}


void ManagerAdministrativo::ocupacionPorDiaDeMedico() {
    system("cls");
    cout << "==============================================" << endl;
    cout << "         OCUPACION POR DIA DE MEDICO          " << endl;
    cout << "==============================================" << endl;

    string dni;
    cout << "\nIngrese el DNI del medico: ";
    cin >> dni;
    cin.ignore();

    Persona personaAux;
    if (!personaAux.validarDNI(dni)) {
        cout << "[!] DNI ingresado no es valido. Intente nuevamente.\n";
        cout << "Presione Enter para continuar...";
        cin.get();
        return;
    }

    ArchivoMedico aMedico("medicos.dat");
    int posMedico = aMedico.BuscarPorDni(dni);
    if (posMedico == -1) {
        cout << "[!] No se encontro ningun medico con ese DNI.\n";
        cout << "Presione Enter para continuar...";
        cin.get();
        return;
    }
    Medico medico = aMedico.Leer(posMedico);

    Fecha fecha = Fecha::leerFechaValida("Ingrese la fecha del turno (DD/MM/AAAA): ");

    cout << "\n----------------------------------------------\n";
    cout << "Medico: " << medico.get_nombre() << " " << medico.get_apellido() << " | DNI: " << dni << endl;
    cout << "Fecha:  " << fecha.toString() << endl;
    cout << "----------------------------------------------\n";

    ArchivoTurno aTurno("turnos.dat");
    ArchivoMedicoEspecialidad aMedEsp("medicoespecialidades.dat");
    ArchivoPaciente aPaciente("paciente.dat");

    // Matriz para guardar los ids medico-especialidad
    const int MAX_RELACIONES = 30;
    int idsMedEsp[MAX_RELACIONES];
    int cantIds = 0;
    for (int i = 0; i < aMedEsp.CantidadRegistros() && cantIds < MAX_RELACIONES; ++i) {
        MedicoEspecialidad me = aMedEsp.Leer(i);
        if (me.getIdMedico() == medico.get_id()) {
            idsMedEsp[cantIds++] = me.getId();
        }
    }

    // Para mostrar resumenes de los turnos
    int cantidad = 0;
    for (int i = 0; i < aTurno.CantidadRegistros(); ++i) {
        Turno t = aTurno.Leer(i);
        Fecha f = t.getFechaAtencion();

        // Buscar si el turno es de este medico
        bool esDelMedico = false;
        for (int j = 0; j < cantIds; ++j) {
            if (t.getIdMedicoEspecialidad() == idsMedEsp[j]) {
                esDelMedico = true;
                break;
            }
        }

        if (esDelMedico && f == fecha && !t.getCancelado() && t.getAsistio()) {
            cantidad++;
        }
    }

    cout << "Turnos atendidos ese dia: " << cantidad << endl;
    cout << "----------------------------------------------\n";

    // Mostrar resumenes si hay turnos
    if (cantidad > 0) {
        cout << "Resumen de turnos atendidos:\n";
        cout << left
             << setw(5) << "ID"
             << setw(20) << "Paciente"
             << setw(8) << "Hora"
             << setw(12) << "Importe"
             << setw(12) << "Sobret."
             << setw(12) << "Asistio"
             << setw(15) << "Obs"
             << endl;
        cout << string(82, '-') << endl;

        for (int i = 0; i < aTurno.CantidadRegistros(); ++i) {
            Turno t = aTurno.Leer(i);
            Fecha f = t.getFechaAtencion();

            bool esDelMedico = false;
            for (int j = 0; j < cantIds; ++j) {
                if (t.getIdMedicoEspecialidad() == idsMedEsp[j]) {
                    esDelMedico = true;
                    break;
                }
            }

            if (esDelMedico && f == fecha && !t.getCancelado() && t.getAsistio()) {
                // Obtener paciente
                int posPac = aPaciente.Buscar(t.getIdPaciente());
                std::string nombrePaciente = "Desconocido";
                if (posPac != -1) {
                    Paciente p = aPaciente.Leer(posPac);
                    nombrePaciente = p.get_nombre() + " " + p.get_apellido();
                }

                cout << left
                     << setw(5) << t.getId()
                     << setw(20) << nombrePaciente
                     << setw(8) << t.getHoraAtencion().toString()
                     << "$" << setw(11) << fixed << setprecision(2) << t.getImporteConsulta()
                     << setw(12) << (t.getSobreturno() ? "Si" : "No")
                     << setw(12) << (t.getAsistio() ? "Si" : "No")
                     << setw(15) << t.getObservaciones()
                     << endl;
            }
        }
    }

    cout << "----------------------------------------------\n";
    cout << "Presione Enter para volver al menu...";
    cin.get();
}

void ManagerAdministrativo::ocupacionPorMesAnioDeMedico() {
    system("cls");
    cout << "==============================================" << endl;
    cout << "      OCUPACION POR MES Y ANIO DE MEDICO      " << endl;
    cout << "==============================================" << endl;

    string dni;
    cout << "\nIngrese el DNI del medico: ";
    cin >> dni;
    cin.ignore();

    Persona personaAux;
    if (!personaAux.validarDNI(dni)) {
        cout << "[!] DNI ingresado no es valido. Intente nuevamente.\n";
        cout << "Presione Enter para continuar...";
        cin.get();
        return;
    }

    ArchivoMedico aMedico("medicos.dat");
    int posMedico = aMedico.BuscarPorDni(dni);
    if (posMedico == -1) {
        cout << "[!] No se encontro ningun medico con ese DNI.\n";
        cout << "Presione Enter para continuar...";
        cin.get();
        return;
    }
    Medico medico = aMedico.Leer(posMedico);

    // Pide mes y año con tu método
    Fecha fecha = Fecha::leerMesAnioValido("Ingrese mes y anio (MM/AAAA): ");
    int mes = fecha.getMes();
    int anio = fecha.getAnio();

    cout << "\n----------------------------------------------\n";
    cout << "Medico: " << medico.get_nombre() << " " << medico.get_apellido() << " | DNI: " << dni << endl;
    cout << "Periodo: " << (mes < 10 ? "0" : "") << mes << "/" << anio << endl;
    cout << "----------------------------------------------\n";

    ArchivoTurno aTurno("turnos.dat");
    ArchivoMedicoEspecialidad aMedEsp("medicoespecialidades.dat");
    ArchivoPaciente aPaciente("paciente.dat");

    const int MAX_RELACIONES = 30;
    int idsMedEsp[MAX_RELACIONES];
    int cantIds = 0;
    for (int i = 0; i < aMedEsp.CantidadRegistros() && cantIds < MAX_RELACIONES; ++i) {
        MedicoEspecialidad me = aMedEsp.Leer(i);
        if (me.getIdMedico() == medico.get_id()) {
            idsMedEsp[cantIds++] = me.getId();
        }
    }

    int cantidad = 0;
    for (int i = 0; i < aTurno.CantidadRegistros(); ++i) {
        Turno t = aTurno.Leer(i);
        Fecha f = t.getFechaAtencion();
        bool esDelMedico = false;
        for (int j = 0; j < cantIds; ++j) {
            if (t.getIdMedicoEspecialidad() == idsMedEsp[j]) {
                esDelMedico = true;
                break;
            }
        }
        if (esDelMedico && f.getMes() == mes && f.getAnio() == anio && !t.getCancelado() && t.getAsistio()) {
            cantidad++;
        }
    }

    cout << "Turnos atendidos en ese periodo: " << cantidad << endl;
    cout << "----------------------------------------------\n";

    // Resumen de los turnos
    if (cantidad > 0) {
        cout << "Resumen de turnos atendidos:\n";
        cout << left
             << setw(5) << "ID"
             << setw(20) << "Paciente"
             << setw(12) << "Fecha"
             << setw(8) << "Hora"
             << setw(12) << "Importe"
             << setw(12) << "Sobret."
             << setw(12) << "Asistio"
             << setw(15) << "Obs"
             << endl;
        cout << string(94, '-') << endl;

        for (int i = 0; i < aTurno.CantidadRegistros(); ++i) {
            Turno t = aTurno.Leer(i);
            Fecha f = t.getFechaAtencion();
            bool esDelMedico = false;
            for (int j = 0; j < cantIds; ++j) {
                if (t.getIdMedicoEspecialidad() == idsMedEsp[j]) {
                    esDelMedico = true;
                    break;
                }
            }
            if (esDelMedico && f.getMes() == mes && f.getAnio() == anio && !t.getCancelado() && t.getAsistio()) {
                int posPac = aPaciente.Buscar(t.getIdPaciente());
                string nombrePaciente = "Desconocido";
                if (posPac != -1) {
                    Paciente p = aPaciente.Leer(posPac);
                    nombrePaciente = p.get_nombre() + " " + p.get_apellido();
                }
                cout << left
                     << setw(5) << t.getId()
                     << setw(20) << nombrePaciente
                     << setw(12) << t.getFechaAtencion().toString()
                     << setw(8) << t.getHoraAtencion().toString()
                     << "$" << setw(11) << fixed << setprecision(2) << t.getImporteConsulta()
                     << setw(12) << (t.getSobreturno() ? "Si" : "No")
                     << setw(12) << (t.getAsistio() ? "Si" : "No")
                     << setw(15) << t.getObservaciones()
                     << endl;
            }
        }
    }
    cout << "----------------------------------------------\n";
    cout << "Presione Enter para volver al menu...";
    cin.get();
}


void ManagerAdministrativo::ocupacionPorMesEspecialidad() {
    system("cls");
    cin.ignore();
    cout << "==============================================" << endl;
    cout << "   OCUPACION POR MES Y ESPECIALIDAD MEDICA    " << endl;
    cout << "==============================================" << endl;

    // Pide mes y año con tu método
    Fecha fecha = Fecha::leerMesAnioValido("Ingrese mes y anio (MM/AAAA): ");
    int mes = fecha.getMes();
    int anio = fecha.getAnio();

    ArchivoTurno aTurno("turnos.dat");
    ArchivoMedicoEspecialidad aME("medicoespecialidades.dat");
    ArchivoEspecialidad aEsp("especialidad.dat");

    const int MAX = 100;
    int turnosPorEspecialidad[MAX] = {0};

    // Cuenta turnos por especialidad
    for (int i = 0; i < aTurno.CantidadRegistros(); i++) {
        Turno t = aTurno.Leer(i);
        Fecha f = t.getFechaAtencion();
        if (f.getMes() == mes && f.getAnio() == anio && !t.getCancelado() && t.getAsistio()) {
            int idME = t.getIdMedicoEspecialidad();
            for (int j = 0; j < aME.CantidadRegistros(); j++) {
                MedicoEspecialidad me = aME.Leer(j);
                if (me.getId() == idME) {
                    int idEsp = me.getIdEspecialidad();
                    if (idEsp > 0 && idEsp <= MAX) turnosPorEspecialidad[idEsp - 1]++;
                    break;
                }
            }
        }
    }

    cout << "\n----------------------------------------------" << endl;
    cout << "Ocupacion medica por especialidad para "
         << (mes < 10 ? "0" : "") << mes << "/" << anio << ":" << endl;
    cout << left << setw(30) << "Especialidad" << "Turnos" << endl;
    cout << string(44, '-') << endl;

    bool hayDatos = false;
    for (int k = 0; k < aEsp.cantidadRegistros(); k++) {
        Especialidad esp = aEsp.leer(k);
        if (turnosPorEspecialidad[k] > 0) {
            cout << left << setw(30) << esp.get_nombreEspecialidad() << turnosPorEspecialidad[k] << endl;
            hayDatos = true;
        }
    }
    if (!hayDatos) {
        cout << "[!] No hubo turnos registrados para ninguna especialidad en ese periodo." << endl;
    }
    cout << "----------------------------------------------" << endl;
    cout << "Presione Enter para volver al menu...";
    cin.ignore();
    cin.get();
}


void ManagerAdministrativo::ocupacionTotalPorMes() {
    system("cls");
    cin.ignore();
    cout << "==============================================" << endl;
    cout << "     OCUPACION TOTAL DE MEDICOS POR MES       " << endl;
    cout << "==============================================" << endl;

    Fecha fecha = Fecha::leerMesAnioValido("Ingrese mes y anio (MM/AAAA): ");
    int mes = fecha.getMes();
    int anio = fecha.getAnio();

    ArchivoTurno aTurno("turnos.dat");
    ArchivoMedico aMedico("medicos.dat");
    ArchivoMedicoEspecialidad aMedEsp("medicoespecialidades.dat");

    const int MAX = 1000;
    int turnosPorMedico[MAX] = {0};

    // Contar turnos para cada medico usando medico-especialidad
    for (int i = 0; i < aTurno.CantidadRegistros(); i++) {
        Turno t = aTurno.Leer(i);
        Fecha f = t.getFechaAtencion();
        if (f.getMes() == mes && f.getAnio() == anio && !t.getCancelado() && t.getAsistio()) {
            int idME = t.getIdMedicoEspecialidad();
            // Buscar el medico para ese idME
            for (int j = 0; j < aMedEsp.CantidadRegistros(); j++) {
                MedicoEspecialidad me = aMedEsp.Leer(j);
                if (me.getId() == idME) {
                    int idMed = me.getIdMedico();
                    if (idMed > 0 && idMed <= MAX) turnosPorMedico[idMed - 1]++;
                    break;
                }
            }
        }
    }

    cout << "\nOcupacion total de todos los medicos para "
         << (mes < 10 ? "0" : "") << mes << "/" << anio << ":" << endl;
    cout << left << setw(6) << "ID"
         << setw(15) << "DNI"
         << setw(20) << "Nombre"
         << setw(20) << "Apellido"
         << right << setw(10) << "Turnos" << endl;
    cout << string(71, '-') << endl;

    bool hayDatos = false;
    for (int i = 0; i < aMedico.CantidadRegistros(); i++) {
        Medico m = aMedico.Leer(i);
        int idMed = m.get_id();
        if (idMed > 0 && idMed <= MAX && turnosPorMedico[idMed - 1] > 0) {
            cout << left << setw(6) << idMed
                 << setw(15) << m.get_dni()
                 << setw(20) << m.get_nombre()
                 << setw(20) << m.get_apellido()
                 << right << setw(10) << turnosPorMedico[idMed - 1] << endl;
            hayDatos = true;
        }
    }

    if (!hayDatos) {
        cout << "[!] No se registraron turnos para ningun medico en ese periodo." << endl;
    }

    cout << string(71, '-') << endl;
    cout << "Presione Enter para volver al menu...";
    cin.ignore();
    cin.get();
}

