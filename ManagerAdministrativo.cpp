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

bool ManagerAdministrativo::compararStringsCaseInsensitive(const std::string& str1, const std::string& str2) {
    if (str1.length() != str2.length()) return false;
    for (size_t i = 0; i < str1.length(); i++) {
        char c1 = str1[i], c2 = str2[i];
        if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
        if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
        if (c1 != c2) return false;
    }
    return true;
}

int ManagerAdministrativo::buscarEspecialidadPorNombre(const char* nombreEspecialidad) {
    ArchivoEspecialidad archivo("especialidad.dat");
    int cantidad = archivo.cantidadRegistros();
    for (int i = 0; i < cantidad; i++) {
        Especialidad esp = archivo.leer(i);
        if (compararStringsCaseInsensitive(esp.get_nombreEspecialidad(), nombreEspecialidad)) return i;
    }
    return -1;
}

float ManagerAdministrativo::obtenerFacturacionDelMes() {
    Fecha fecha = Fecha::leerFechaValida("Ingrese mes y año (01/aaaa): ");
    int mes = fecha.getMes();
    int anio = fecha.getAnio();

    ArchivoTurno archivo("turnos.dat");
    float total = 0;
    for (int i = 0; i < archivo.CantidadRegistros(); i++) {
        Turno t = archivo.Leer(i);
        Fecha f = t.getFechaAtencion();
        if (f.getMes() == mes && f.getAnio() == anio && !t.getCancelado() && t.getAsistio()) {
            total += t.getImporteConsulta();
        }
    }
    cout << fixed << setprecision(2);
    cout << "Facturación total para " << mes << "/" << anio << ": $ " << total << endl;
    system("pause");
    return total;
}

void ManagerAdministrativo::listarPacientesAtendidosPorEspecialidadYMes() {
    Fecha fecha = Fecha::leerFechaValida("Ingrese mes y año (01/aaaa): ");
    int mes = fecha.getMes();
    int anio = fecha.getAnio();
    int idEsp;
    cout << "Ingrese el ID de especialidad: ";
    cin >> idEsp;

    ArchivoTurno aTurno("turnos.dat");
    ArchivoMedicoEspecialidad aME("medicoespecialidad.dat");
    ArchivoPaciente aPaciente("paciente.dat");

    bool hayPacientes = false;
    cout << "\nPacientes atendidos en " << mes << "/" << anio << " para especialidad ID " << idEsp << ":\n";

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
    if (!hayPacientes) cout << "No se encontraron pacientes atendidos.\n";
    system("pause");
}

void ManagerAdministrativo::ocupacionPorDiaDeMedico() {
    string dni;
    cout << "Ingrese el DNI del médico: ";
    cin >> dni;

    // Limpiar buffer para que getline funcione correctamente en leerFechaValida
    string salto;
    getline(cin, salto);

    Persona personaAux;
    if (!personaAux.validarDNI(dni)) {
        cout << "DNI inválido.\n";
        system("pause");
        return;
    }

    Fecha fecha = Fecha::leerFechaValida("Ingrese la fecha del turno (dd/mm/aaaa): ");

    ArchivoTurno aTurno("turnos.dat");
    ArchivoMedico aMedico("medico.dat");

    int idMedico = -1;
    for (int i = 0; i < aMedico.CantidadRegistros(); i++) {
        Medico m = aMedico.Leer(i);
        if (m.get_dni() == dni) {
            idMedico = m.get_id();
            break;
        }
    }
    if (idMedico == -1) {
        cout << "Médico no encontrado.\n";
        system("pause");
        return;
    }

    int cantidad = 0;
    for (int i = 0; i < aTurno.CantidadRegistros(); i++) {
        Turno t = aTurno.Leer(i);
        Fecha f = t.getFechaAtencion();
        if (t.getIdMedicoEspecialidad() == idMedico && f == fecha && !t.getCancelado() && t.getAsistio()) {
            cantidad++;
        }
    }

    cout << "\nDNI: " << dni << " | Fecha: " << fecha.toString() << " | Turnos Atendidos: " << cantidad << endl;
    system("pause");
}
bool ManagerAdministrativo::pedirMesAnio(int &mes, int &anio) {
    char entrada[20];
    while (true) {
        std::cout << "Ingrese mes y año (MM/AAAA) o 0 para salir: ";
        std::cin.getline(entrada, 20);

        // Si el usuario sólo escribió '0' y enter, cancela
        if (entrada[0] == '0' && entrada[1] == '\0') {
            return false; // Canceló
        }

        // Buscar '/' manualmente
        int posSeparador = -1;
        for (int i = 0; entrada[i] != '\0'; i++) {
            if (entrada[i] == '/') {
                posSeparador = i;
                break;
            }
        }
        if (posSeparador == -1) {
            std::cout << "[!] Formato incorrecto. Debe ser MM/AAAA.\n";
            continue;
        }

        // Separar mes y año en cadenas char
        char mesStr[3] = {'\0', '\0', '\0'};
        char anioStr[10] = {'\0'};

        // Copiar mes (antes del separador)
        int i;
        for (i = 0; i < posSeparador && i < 2; i++) {
            mesStr[i] = entrada[i];
        }
        mesStr[i] = '\0';

        // Copiar año (después del separador)
        int j = 0;
        for (i = posSeparador + 1; entrada[i] != '\0' && j < 9; i++, j++) {
            anioStr[j] = entrada[i];
        }
        anioStr[j] = '\0';

        // Validar que mesStr y anioStr sólo tengan dígitos
        bool mesEsNumero = true;
        for (int k = 0; mesStr[k] != '\0'; k++) {
            if (mesStr[k] < '0' || mesStr[k] > '9') {
                mesEsNumero = false;
                break;
            }
        }
        bool anioEsNumero = true;
        for (int k = 0; anioStr[k] != '\0'; k++) {
            if (anioStr[k] < '0' || anioStr[k] > '9') {
                anioEsNumero = false;
                break;
            }
        }
        if (!mesEsNumero || !anioEsNumero) {
            std::cout << "[!] Mes y año deben ser números.\n";
            continue;
        }

        // Convertir mesStr a int
        mes = 0;
        for (int k = 0; mesStr[k] != '\0'; k++) {
            mes = mes * 10 + (mesStr[k] - '0');
        }
        // Convertir anioStr a int
        anio = 0;
        for (int k = 0; anioStr[k] != '\0'; k++) {
            anio = anio * 10 + (anioStr[k] - '0');
        }

        // Validar rango
        if (mes < 1 || mes > 12) {
            std::cout << "[!] Mes inválido. Debe estar entre 1 y 12.\n";
            continue;
        }
        if (anio < 1) {
            std::cout << "[!] Año inválido. Debe ser positivo.\n";
            continue;
        }

        return true; // Entrada válida
    }
}

void ManagerAdministrativo::ocupacionPorMesDeMedico() {
    string dni;
    cout << "Ingrese el DNI del médico: ";
    cin >> dni;

    // Limpiar buffer para evitar que getline en pedirMesAnio tome línea vacía
    string salto;
    getline(cin, salto);

    Persona personaAux;
    if (!personaAux.validarDNI(dni)) {
        cout << "DNI inválido.\n";
        system("pause");
        return;
    }

    int mes, anio;
    if (!pedirMesAnio(mes, anio)) {
        cout << "Operación cancelada.\n";
        system("pause");
        return;
    }

    ArchivoTurno aTurno("turnos.dat");
    ArchivoMedico aMedico("medico.dat");

    int idMedico = -1;
    for (int i = 0; i < aMedico.CantidadRegistros(); i++) {
        Medico m = aMedico.Leer(i);
        if (m.get_dni() == dni) {
            idMedico = m.get_id();
            break;
        }
    }
    if (idMedico == -1) {
        cout << "Médico no encontrado.\n";
        system("pause");
        return;
    }

    int cantidad = 0;
    for (int i = 0; i < aTurno.CantidadRegistros(); i++) {
        Turno t = aTurno.Leer(i);
        Fecha f = t.getFechaAtencion();
        if (t.getIdMedicoEspecialidad() == idMedico && f.getMes() == mes && f.getAnio() == anio && !t.getCancelado() && t.getAsistio()) {
            cantidad++;
        }
    }

    cout << "\nDNI: " << dni << " | Mes: " << mes << "/" << anio << " | Turnos Atendidos: " << cantidad << endl;
    system("pause");
}

void ManagerAdministrativo::ocupacionPorMesEspecialidad() {
    Fecha fecha = Fecha::leerFechaValida("Ingrese mes y año (01/aaaa): ");
    int mes = fecha.getMes();
    int anio = fecha.getAnio();

    ArchivoTurno aTurno("turnos.dat");
    ArchivoMedicoEspecialidad aME("medicoespecialidad.dat");
    ArchivoEspecialidad aEsp("especialidad.dat");

    const int MAX = 100;
    int turnosPorEspecialidad[MAX] = {0};

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

    cout << "\nOcupación médica por especialidad para " << mes << "/" << anio << ":\n";
    cout << left << setw(30) << "Especialidad" << "Turnos\n";
    cout << "-------------------------------------------\n";

    for (int k = 0; k < aEsp.cantidadRegistros(); k++) {
        Especialidad esp = aEsp.leer(k);
        int idEsp = k + 1;
        if (turnosPorEspecialidad[k] > 0) {
            cout << left << setw(30) << esp.get_nombreEspecialidad() << turnosPorEspecialidad[k] << "\n";
        }
    }
    system("pause");
}

void ManagerAdministrativo::ocupacionTotalPorMes() {
    Fecha fecha = Fecha::leerFechaValida("Ingrese mes y año (01/aaaa): ");
    int mes = fecha.getMes();
    int anio = fecha.getAnio();

    ArchivoTurno aTurno("turnos.dat");
    ArchivoMedico aMedico("medico.dat");

    const int MAX = 1000;
    int turnosPorMedico[MAX] = {0};

    for (int i = 0; i < aTurno.CantidadRegistros(); i++) {
        Turno t = aTurno.Leer(i);
        Fecha f = t.getFechaAtencion();
        if (f.getMes() == mes && f.getAnio() == anio && !t.getCancelado() && t.getAsistio()) {
            int idMed = t.getIdMedicoEspecialidad();
            if (idMed > 0 && idMed <= MAX) turnosPorMedico[idMed - 1]++;
        }
    }

    cout << "\nOcupación total de todos los médicos para " << mes << "/" << anio << ":\n";
    cout << left << setw(6) << "ID" << setw(15) << "DNI" << setw(20) << "Nombre" << setw(20) << "Apellido" << right << setw(10) << "Turnos\n";
    cout << "------------------------------------------------------------------\n";

    for (int i = 0; i < aMedico.CantidadRegistros(); i++) {
        Medico m = aMedico.Leer(i);
        int idMed = m.get_id();
        if (idMed > 0 && idMed <= MAX && turnosPorMedico[idMed - 1] > 0) {
            cout << left << setw(6) << idMed
                 << setw(15) << m.get_dni()
                 << setw(20) << m.get_nombre()
                 << setw(20) << m.get_apellido()
                 << right << setw(10) << turnosPorMedico[idMed - 1] << "\n";
        }
    }
    system("pause");
}
