#include "Menu.h"
#include "ManagerPaciente.h"
#include <iostream>

using namespace std;

// Constructor vacío
Menu::Menu() {}

// Menú principal del sistema
void Menu::menuPrincipal() {
    int opcion;
    do {
        cout << "========== MENU PRINCIPAL ==========" << endl;
        cout << "1. Menu de Pacientes" << endl;
        cout << "2. Menu de Medicos" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                menuPaciente();
                break;
            case 2:
                menuMedico();
                break;
            case 0:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }

        cout << endl;
    } while (opcion != 0);
}

// Menú de opciones para pacientes
void Menu::menuPaciente() {
    ManagerPaciente managerPaciente;
    int opcion;
    do {
        cout << "---------- MENU PACIENTES ----------" << endl;
        cout << "1. Cargar nuevo paciente" << endl;
        cout << "2. Listar pacientes" << endl;
        cout << "3. Modificar paciente" << endl;
        cout << "4. Buscar paciente por DNI" << endl;
        cout << "5. Sacar turno" << endl;
        cout << "6. Ver turnos" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: managerPaciente.crearNuevoPaciente();
                break;

            case 2:managerPaciente.ListarTodos();
                break;

            case 3:managerPaciente.EditarPaciente();
                break;

            case 4:managerPaciente.MostrarPorDni();
                break;

            case 5:
                cout << "Sacar turno (opción aún no implementada)." << endl;
                break;
            case 6:
                cout << "Ver turnos (opción aún no implementada)." << endl;
                break;
            case 0:
                cout << "Volviendo al menú principal..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }

        cout << endl;
    } while (opcion != 0);
}

// Menú de opciones para médicos
void Menu::menuMedico() {
    int opcion;
    do {
        cout << "---------- MENU MEDICOS ----------" << endl;
        cout << "1. Registrar nuevo medico" << endl;
        cout << "2. Listar medicos" << endl;
        cout << "3. Modificar medico" << endl;
        cout << "4. Buscar medico por ID" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Registrar nuevo medico (opción aún no implementada)." << endl;
                break;
            case 2:
                cout << "Listar medicos (opción aún no implementada)." << endl;
                break;
            case 3:
                cout << "Modificar medico (opción aún no implementada)." << endl;
                break;
            case 4:
                cout << "Buscar medico por ID (opción aún no implementada)." << endl;
                break;
            case 0:
                cout << "Volviendo al menú principal..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }

        cout << endl;
    } while (opcion != 0);
}
