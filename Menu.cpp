#include "Menu.h"
#include "ManagerPaciente.h"
#include <iostream>
#include "ManagerMedico.h"
#include "ManagerTurno.h"
#include "ManagerEspecialidad.h"
#include "ManagerMedicoEspecialidad.h"

using namespace std;

// Menu principal del sistema
void Menu::menuPrincipal()
{
    int opcion;
    do
    {
        menuHeader();
        cout << "\n------------ Menu Principal -----------\n";
        cout << "  1) Pacientes\n";
        cout << "  2) Medicos\n";
        cout << "  3) Turnos\n";
        cout << "----------------------------------------\n";
        cout << "  0) Salir\n";
        cout << "----------------------------------------\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            system("cls");
            menuHeader();
            menuPaciente();
            break;
        case 2:
            system("cls");
            menuHeader();
            menuMedico();
            break;
        case 3:
            system("cls");
            menuHeader();
            menuTurnos();
            break;
        case 0:
            cout << "Saliendo del sistema..." << endl;
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
        }

        cout << endl;
    }
    while (opcion != 0);
}

// Menu de opciones para pacientes
void Menu::menuPaciente()
{
    ManagerPaciente managerPaciente;
    ManagerTurno managerTurno;
    int opcion;
    do
    {
        cout << "\n-------------- PACIENTES --------------\n";
        cout << "  1) Registrar nuevo paciente\n";
        cout << "  2) Listar pacientes\n";
        cout << "  3) Modificar paciente\n";
        cout << "  4) Buscar paciente por documento\n";
        cout << "  5) Sacar turno\n";
        cout << "  6) Ver turnos\n";
        cout << "----------------------------------------\n";
        cout << "  0) Volver al menu principal\n";
        cout << "----------------------------------------\n";
        cout << "Seleccione una opcion: ";
        cout << endl;
        cin >> opcion;

        switch (opcion) {
            case 1: managerPaciente.crearNuevoPaciente();
                break;

            case 2: managerPaciente.ListarTodos();
                break;

            case 3: managerPaciente.EditarPaciente();
                break;

            case 4: managerPaciente.MostrarPorDni();
                break;

            case 5:
                  managerTurno.sacarTurno();
                break;
            case 6:
                 managerTurno.mostrarAgendaSemanal();
                break;
            case 0:
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;

        }
        cout << endl;
    }
    while (opcion != 0);
}

// Menu de opciones para medicos
void Menu::menuMedico()
{
    ManagerMedico manager;
    ManagerEspecialidad managerEsp;
    ManagerMedicoEspecialidad managerMedEsp;

    int opcion;
    do
    {
        cout << "\n---------------- MEDICOS ---------------\n";
        cout << "  1) Registrar nuevo medico\n";
        cout << "  2) Listar medicos\n";
        cout << "  3) Modificar medico\n";
        cout << "  4) Buscar medico por documento\n";
        cout << "  5) Registrar especialidad\n";
        cout << "  6) Listar especialidades\n";
        cout << "  7) Modificar especialidad\n";
        cout << "  8) Eliminar especialidad\n";
        cout << "  9) Asignar especialidad a medico\n";
        cout << " 10) Quitar especialidad a medico\n";
        cout << " 11) Ver relaciones medico-especialidad\n";
        cout << "----------------------------------------\n";
        cout << "  0) Volver al menu principal\n";
        cout << "----------------------------------------\n";
        cout << "Seleccione una opcion: ";
        cout << endl;
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            manager.registrarNuevoMedico();
            break;
        case 2:
            manager.listarMedicos();
            break;
        case 3:
            manager.modificarMedicoPorDni();
            break;
        case 4:
            manager.buscarYMostrarMedicoPorDni();
            break;
        case 5:
            managerEsp.cargarEspecialidad();
            break;
        case 6:
            managerEsp.listarEspecialidades();
            break;
        case 7:
            managerEsp.editarEspecialidad();
            break;
        case 8:
            managerEsp.eliminarEspecialidad();
            break;
        case 9:
            managerMedEsp.cargarMedicoEspecialidad();
            break;
        case 10:
            managerMedEsp.eliminarMedicoEspecialidad();
            break;
        case 11:
            managerMedEsp.listarMedicoEspecialidad();
            break;
        case 0:
            cout << "Volviendo al menu principal..." << endl;
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
        }

        cout << endl;
    }
    while (opcion != 0);
}

void Menu::menuTurnos() {
    ManagerTurno manager;
    int opcion;
    do {
        cout << "\n----------------- TURNOS ----------------\n";
        cout << "  1) Sacar nuevo turno\n";
        cout << "  2) Ver agenda semanal\n";
        cout << "  3) Buscar turno por ID\n";
        cout << "  4) Listar todos los turnos\n";
        cout << "----------------------------------------\n";
        cout << "  0) Volver al menu principal\n";
        cout << "----------------------------------------\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                manager.sacarTurno();
                break;
            case 2:
                manager.mostrarAgendaSemanal();
                break;
            case 3: {
                int id;
                cout << "Ingrese el ID del turno a buscar: ";
                cin >> id;
                break;
            }
            case 4: manager.listarTurnos() ;
                break;
            case 0:
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }
        cout << endl;
    } while (opcion != 0);
}

void Menu::menuHeader(){
        cout << "\n========================================\n";
        cout << "           SISTEMA DE CONSULTORIO        \n";
        cout << "========================================\n";
};
