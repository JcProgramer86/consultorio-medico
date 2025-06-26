#include "ManagerAdministrativo.h"
#include "ArchivoTurno.h"
#include "ArchivoMedicoEspecialidad.h"
#include "ArchivoPaciente.h"
#include "ArchivoMedico.h"
#include "ArchivoEspecialidad.h"
#include "Especialidad.h"
#include "Fecha.h"
#include "Persona.h"
#include "Medico.h"
#include "Paciente.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

ManagerAdministrativo::ManagerAdministrativo() {}

// Método auxiliar para comparar strings ignorando mayúsculas/minúsculas
bool ManagerAdministrativo::compararStringsCaseInsensitive(const string& str1, const string& str2)
{
    if (str1.length() != str2.length()) return false;
    for (size_t i = 0; i < str1.length(); i++)
    {
        char c1 = str1[i], c2 = str2[i];
        if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
        if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
        if (c1 != c2) return false;
    }
    return true;
}

int ManagerAdministrativo::obtenerIdMedicoPorDni(const std::string& dni) {
    ArchivoMedico archivoMedico("medicos.dat");
    int pos = archivoMedico.BuscarPorDni(dni);
    if (pos == -1) return -1;

    Medico medico = archivoMedico.Leer(pos);
    return medico.get_id();
}

int ManagerAdministrativo::obtenerIdPacientePorDni(const std::string& dni) {
    ArchivoPaciente aPaciente("paciente.dat");
    int pos = aPaciente.BuscarPorDni(dni);
    if (pos == -1) return -1;

    Paciente p = aPaciente.Leer(pos);
    return p.get_id();
}


// Busca especialidad por nombre (ignorando mayúsculas)
int ManagerAdministrativo::buscarEspecialidadPorNombre(const char* nombreEspecialidad)
{
    ArchivoEspecialidad archivo("especialidad.dat");
    int cantidad = archivo.cantidadRegistros();
    for (int i = 0; i < cantidad; i++)
    {
        Especialidad esp = archivo.leer(i);
        if (compararStringsCaseInsensitive(esp.get_nombreEspecialidad(), nombreEspecialidad)) return i;
    }
    return -1;
}

// Solicita al usuario una especialidad por ID o nombre
int ManagerAdministrativo::pedirEspecialidad()
{
    ArchivoEspecialidad archivo("especialidad.dat");
    char entrada[100];

    while (true)
    {

        cout << "Ingrese ID o Nombre de la especialidad (0 para cancelar): ";
        cin.getline(entrada, 100);

        if (entrada[0] == '0' && entrada[1] == '\0')
        {
            return -1;
        }

        bool esNumero = true;
        for (int i = 0; entrada[i] != '\0'; i++)
        {
            if (entrada[i] < '0' || entrada[i] > '9')
            {
                esNumero = false;
                break;
            }
        }

        if (esNumero)
        {
            int id = 0;
            for (int i = 0; entrada[i] != '\0'; i++)
            {
                id = id * 10 + (entrada[i] - '0');
            }

            if (id > 0 && id <= archivo.cantidadRegistros())
            {
                return id;
            }
            else
            {
                cout << "ID inválido. Intente de nuevo.\n";
                system("pause");
            }
        }
        else
        {
            int pos = buscarEspecialidadPorNombre(entrada);
            if (pos != -1)
            {
                return pos + 1;
            }
            cout << "No se encontró especialidad con ese nombre. Intente de nuevo.\n";
            system("pause");
        }
    }
}

// Solicita mes y año en formato MM/AAAA
bool ManagerAdministrativo::pedirMesAnio(int &mes, int &anio)
{
    char entrada[20];
    while (true)
    {

        cout << "Ingrese mes y año (MM/AAAA) o 0 para salir: ";
        cin.getline(entrada, 20);

        if (entrada[0] == '0' && entrada[1] == '\0')
        {
            return false;
        }

        int posSeparador = -1;
        for (int i = 0; entrada[i] != '\0'; i++)
        {
            if (entrada[i] == '/')
            {
                posSeparador = i;
                break;
            }
        }
        if (posSeparador == -1)
        {
            cout << "[!] Formato incorrecto. Debe ser MM/AAAA.\n";
            system("pause");
            continue;
        }

        char mesStr[3] = {'\0', '\0', '\0'};
        char anioStr[10] = {'\0'};

        int i;
        for (i = 0; i < posSeparador && i < 2; i++)
        {
            mesStr[i] = entrada[i];
        }
        mesStr[i] = '\0';

        int j = 0;
        for (i = posSeparador + 1; entrada[i] != '\0' && j < 9; i++, j++)
        {
            anioStr[j] = entrada[i];
        }
        anioStr[j] = '\0';

        bool mesEsNumero = true;
        for (int k = 0; mesStr[k] != '\0'; k++)
        {
            if (mesStr[k] < '0' || mesStr[k] > '9')
            {
                mesEsNumero = false;
                break;
            }
        }
        bool anioEsNumero = true;
        for (int k = 0; anioStr[k] != '\0'; k++)
        {
            if (anioStr[k] < '0' || anioStr[k] > '9')
            {
                anioEsNumero = false;
                break;
            }
        }
        if (!mesEsNumero || !anioEsNumero)
        {
            cout << "[!] Mes y año deben ser números.\n";
            system("pause");
            continue;
        }

        mes = 0;
        for (int k = 0; mesStr[k] != '\0'; k++)
        {
            mes = mes * 10 + (mesStr[k] - '0');
        }

        anio = 0;
        for (int k = 0; anioStr[k] != '\0'; k++)
        {
            anio = anio * 10 + (anioStr[k] - '0');
        }

        if (mes < 1 || mes > 12)
        {
            cout << "[!] Mes inválido. Debe estar entre 1 y 12.\n";
            system("pause");
            continue;
        }
        if (anio < 1)
        {
            cout << "[!] Año inválido. Debe ser positivo.\n";
            system("pause");
            continue;
        }

        return true;
    }
}

// Obtiene facturación total de un mes/año
float ManagerAdministrativo::obtenerFacturacionDelMes()
{
    system("cls");

    int mes, anio;
    string salto;
    getline(cin, salto);

    if (!pedirMesAnio(mes, anio))
    {
        cout << "Operación cancelada.\n";
        system("pause");
        return 0;
    }

    ArchivoTurno archivo("turnos.dat");
    float total = 0;

    for (int i = 0; i < archivo.CantidadRegistros(); i++)
    {
        Turno t = archivo.Leer(i);
        Fecha f = t.getFechaAtencion();
        if (f.getMes() == mes && f.getAnio() == anio && !t.getCancelado() && t.getAsistio())
        {
            total += t.getImporteConsulta();
        }
    }

    cout << fixed << setprecision(2);
    cout << "Facturación total para " << mes << "/" << anio << ": $ " << total << endl;
    system("pause");
    return total;
}
void ManagerAdministrativo::mostrarEspecialidades()
{
    ArchivoEspecialidad aEspecialidad("especialidad.dat");
    int cantidad = aEspecialidad.cantidadRegistros();

    if (cantidad == 0)
    {
        cout << "No hay especialidades cargadas.\n";
        return;
    }

    cout << "Especialidades disponibles:\n";
    cout << left << setw(5) << "ID" << "Nombre\n";
    cout << "--------------------------\n";

    for (int i = 0; i < cantidad; i++)
    {
        Especialidad esp = aEspecialidad.leer(i);
        cout << left << setw(5) << esp.get_id() << esp.get_nombreEspecialidad() << "\n";
    }
    cout << "\n";
}


// Lista pacientes atendidos por especialidad y mes
void ManagerAdministrativo::listarPacientesAtendidosPorEspecialidadYMes()
{
    int mes, anio;
    string salto;
    getline(cin, salto);

    // Pedir mes y año
    if (!pedirMesAnio(mes, anio))
    {
        cout << "Operación cancelada.\n";
        system("pause");
        return;
    }

    // Mostrar las especialidades disponibles
    ArchivoEspecialidad aEspecialidad("especialidad.dat");
    cout << "\nEspecialidades disponibles:\n";
    cout << "ID   Nombre\n";
    cout << "--------------------------\n";
    for (int i = 0; i < aEspecialidad.cantidadRegistros(); i++) {
        Especialidad esp = aEspecialidad.leer(i);
        cout << esp.get_id() << "    " << esp.get_nombreEspecialidad() << "\n";
    }

    // Solicitar ID o nombre de especialidad
    int idEsp = pedirEspecialidad();
    if (idEsp == 0)  // Salir si el usuario ingresa 0
    {
        cout << "Operación cancelada.\n";
        system("pause");
        return;
    }

    // Obtener nombre de la especialidad seleccionada
    string nombreEspecialidad = "Desconocida";
    int posEsp = aEspecialidad.buscarPorId(idEsp); // Verificar si la especialidad existe
    if (posEsp != -1)
    {
        Especialidad esp = aEspecialidad.leer(posEsp);
        nombreEspecialidad = esp.get_nombreEspecialidad();
    }

    bool hayPacientes = false;
    int contador = 0;

    cout << "\nPacientes atendidos en " << mes << "/" << anio
         << " para especialidad: " << nombreEspecialidad << " (ID: " << idEsp << ")\n\n";

    cout << left << setw(5) << "N°"
         << setw(20) << "Nombre"
         << setw(20) << "Apellido"
         << setw(10) << "ID"
         << "\n-----------------------------------------------\n";

    // Itera por todos los turnos
    ArchivoTurno aTurno("turnos.dat");
    ArchivoMedicoEspecialidad aME("medicoespecialidad.dat");
    ArchivoPaciente aPaciente("paciente.dat");

    for (int i = 0; i < aTurno.CantidadRegistros(); i++)
    {
        Turno t = aTurno.Leer(i);
        Fecha f = t.getFechaAtencion();

        // Verifica si el turno es del mes y año deseado
        if (f.getMes() == mes && f.getAnio() == anio && t.getAsistio() && !t.getCancelado())
        {
            // El problema está aquí: si posME es -1, no hay MedicoEspecialidad.
            // No podemos saberlo de antemano sin leer todo el archivo,
            // así que simplemente omitiremos el mensaje si no se encuentra.

            int posME = aME.Buscar(t.getIdMedicoEspecialidad());

            // Si posME es -1, significa que el ID no se encontró.
            // En lugar de imprimir el error, simplemente no entramos al 'else'
            // y el turno no se procesa.
            if (posME != -1) // SOLO SI ENCUENTRA LA RELACION MEDICO-ESPECIALIDAD
            {
                MedicoEspecialidad me = aME.Leer(posME);
                // cout << "  MedicoEspecialidad encontrado: IDEspecialidad = " << me.getIdEspecialidad() << "\n"; // Esto también podrías quitarlo

                // Verifica si el ID de la especialidad del médico coincide con la especialidad seleccionada
                if (me.getIdEspecialidad() == idEsp)
                {
                    int posPac = aPaciente.Buscar(t.getIdPaciente());
                    if (posPac != -1)
                    {
                        Paciente p = aPaciente.Leer(posPac);
                        contador++;
                        cout << setw(5) << contador
                             << setw(20) << p.get_nombre()
                             << setw(20) << p.get_apellido()
                             << setw(10) << p.get_id()
                             << "\n";
                        hayPacientes = true;
                    }
                    // else {
                    //     cout << "  No se encontró paciente con ID: " << t.getIdPaciente() << "\n"; // Puedes decidir si mostrar esto
                    // }
                }
                // else {
                //     cout << "  El ID de especialidad del médico no coincide con la especialidad seleccionada.\n"; // Puedes decidir si mostrar esto
                // }
            }
            // else {
            //     // ANTES: Aquí se imprimía el error. Ahora simplemente NO hacemos nada
            //     // con los turnos que tienen un ID de MedicoEspecialidad que no existe.
            // }
        }
    }

    // Si no hay pacientes, se muestra un mensaje
    if (!hayPacientes)
    {
        cout << "No se encontraron pacientes atendidos.\n";
    }

    system("pause");
}


// Ocupación por día de un médico
void ManagerAdministrativo::ocupacionPorDiaDeMedico()
{
    system("cls");

    string dni;
    cout << "Ingrese el DNI del médico: ";
    cin >> dni;
    cin.ignore();  // Limpio el buffer para evitar problemas al leer después

    Persona personaAux;
    if (!personaAux.validarDNI(dni))
    {
        cout << "DNI inválido.\n";
        system("pause");
        return;
    }

    Fecha fecha = Fecha::leerFechaValida("Ingrese la fecha del turno (dd/mm/aaaa): ");

    int idMedico = obtenerIdMedicoPorDni(dni);
    if (idMedico == -1)
    {
        cout << "Médico no encontrado.\n";
        system("pause");
        return;
    }

    ArchivoTurno aTurno("turnos.dat");

    int cantidad = 0;
    int totalTurnos = aTurno.CantidadRegistros();
    for (int i = 0; i < totalTurnos; i++)
    {
        Turno t = aTurno.Leer(i);
        Fecha f = t.getFechaAtencion();

        if (t.getIdMedicoEspecialidad() == idMedico && f == fecha && !t.getCancelado() && t.getAsistio())
        {
            cantidad++;
        }
    }

    cout << "\nDNI: " << dni << " | Fecha: " << fecha.toString() << " | Turnos Atendidos: " << cantidad << endl;
    system("pause");
}


void ManagerAdministrativo::ocupacionPorMesDeMedico()
{
    system("cls");

    string dni;
    cout << "Ingrese el DNI del médico: ";
    cin >> dni;
    cin.ignore();  // para limpiar el buffer

    Persona personaAux;
    if (!personaAux.validarDNI(dni))
    {
        cout << "DNI inválido.\n";
        system("pause");
        return;
    }

    int mes, anio;
    if (!pedirMesAnio(mes, anio))
    {
        cout << "Operación cancelada.\n";
        system("pause");
        return;
    }

    int idMedico = obtenerIdMedicoPorDni(dni);
    if (idMedico == -1)
    {
        cout << "Médico no encontrado.\n";
        system("pause");
        return;
    }

    ArchivoTurno aTurno("turnos.dat");

    int cantidad = 0;
    int totalTurnos = aTurno.CantidadRegistros();
    for (int i = 0; i < totalTurnos; i++)
    {
        Turno t = aTurno.Leer(i);
        Fecha f = t.getFechaAtencion();
        if (t.getIdMedicoEspecialidad() == idMedico && f.getMes() == mes && f.getAnio() == anio && !t.getCancelado() && t.getAsistio())
        {
            cantidad++;
        }
    }

    cout << "\nDNI: " << dni << " | Mes: " << mes << "/" << anio << " | Turnos Atendidos: " << cantidad << endl;
    system("pause");
}


// Ocupación por mes y especialidad (Resumen general)
void ManagerAdministrativo::ocupacionPorMesEspecialidad()
{
    system("cls");

    int mes, anio;

    string salto;
    getline(cin, salto);

    if (!pedirMesAnio(mes, anio))
    {
        cout << "Operación cancelada.\n";
        system("pause");
        return;
    }

    ArchivoTurno aTurno("turnos.dat");
    ArchivoMedicoEspecialidad aME("medicoespecialidad.dat");
    ArchivoEspecialidad aEsp("especialidad.dat");

    const int MAX = 100;
    int turnosPorEspecialidad[MAX] = {0};

    for (int i = 0; i < aTurno.CantidadRegistros(); i++)
    {
        Turno t = aTurno.Leer(i);
        Fecha f = t.getFechaAtencion();
        if (f.getMes() == mes && f.getAnio() == anio && !t.getCancelado() && t.getAsistio())
        {
            int idME = t.getIdMedicoEspecialidad();
            for (int j = 0; j < aME.CantidadRegistros(); j++)
            {
                MedicoEspecialidad me = aME.Leer(j);
                if (me.getId() == idME)
                {
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

    for (int k = 0; k < aEsp.cantidadRegistros(); k++)
    {
        Especialidad esp = aEsp.leer(k);

        if (turnosPorEspecialidad[k] > 0)
        {
            cout << left << setw(30) << esp.get_nombreEspecialidad() << turnosPorEspecialidad[k] << "\n";
        }
    }
    system("pause");
}

// Ocupación total por mes (todos los médicos)
void ManagerAdministrativo::ocupacionTotalPorMes()
{
    system("cls");

    int mes, anio;

    string salto;
    getline(cin, salto);

    if (!pedirMesAnio(mes, anio))
    {
        cout << "Operación cancelada.\n";
        system("pause");
        return;
    }

    ArchivoTurno aTurno("turnos.dat");
    ArchivoMedico aMedico("medico.dat");

    const int MAX = 1000;
    int turnosPorMedico[MAX] = {0};

    for (int i = 0; i < aTurno.CantidadRegistros(); i++)
    {
        Turno t = aTurno.Leer(i);
        Fecha f = t.getFechaAtencion();
        if (f.getMes() == mes && f.getAnio() == anio && !t.getCancelado() && t.getAsistio())
        {
            int idMed = t.getIdMedicoEspecialidad();
            if (idMed > 0 && idMed <= MAX) turnosPorMedico[idMed - 1]++;
        }
    }

    cout << "\nOcupación total de todos los médicos para " << mes << "/" << anio << ":\n";
    cout << left << setw(6) << "ID" << setw(15) << "DNI" << setw(20) << "Nombre" << setw(20) << "Apellido" << right << setw(10) << "Turnos\n";
    cout << "------------------------------------------------------------------\n";

    for (int i = 0; i < aMedico.CantidadRegistros(); i++)
    {
        Medico m = aMedico.Leer(i);
        int idMed = m.get_id();
        if (idMed > 0 && idMed <= MAX && turnosPorMedico[idMed - 1] > 0)
        {
            cout << left << setw(6) << idMed
                 << setw(15) << m.get_dni()
                 << setw(20) << m.get_nombre()
                 << setw(20) << m.get_apellido()
                 << right << setw(10) << turnosPorMedico[idMed - 1] << "\n";
        }
    }
    system("pause");
}
