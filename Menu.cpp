#include "Menu.h"
#include "ManagerPaciente.h"
#include <iostream>
#include "ManagerMedico.h"
#include "ManagerTurno.h"
#include "ManagerEspecialidad.h"
#include "ManagerMedicoEspecialidad.h"
#include "ManagerAdministrativo.h"
#include "ManagerPrestador.h"

using namespace std;

// Menu principal del sistema
void Menu::menuPrincipal()
{
    int opcion;
    do
    {
        system("cls");
        menuHeader();
        cout << "\n------------ Menu Principal -----------\n";
        cout << "  1) Pacientes\n";
        cout << "  2) Medicos\n";
        cout << "  3) Turnos\n";
        cout << "  4) Prestadores\n";
        cout << "  5) Administrativo\n";
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
        case 4:
            system("cls");
            menuHeader();
            menuPrestador();
            break;
        case 5:
            system("cls");
            menuHeader();
            menuAdministrativo();
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
        system("cls");
        menuHeader();
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

        switch (opcion)
        {
        case 1:
            system("cls");
            menuHeader();
            managerPaciente.crearNuevoPaciente();
            break;

        case 2:
            system("cls");
            menuHeader();
            managerPaciente.ListarTodos();
            break;

        case 3:
            system("cls");
            menuHeader();
            managerPaciente.EditarPaciente();
            break;

        case 4:
            system("cls");
            menuHeader();
            managerPaciente.MostrarPorDni();
            break;

        case 5:
            system("cls");
            menuHeader();
            managerTurno.sacarTurno();
            break;
        case 6:
            system("cls");
            menuHeader();
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
        system("cls");
        menuHeader();
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
            system("cls");
            menuHeader();
            manager.registrarNuevoMedico();
            break;
        case 2:
            system("cls");
            menuHeader();
            manager.listarMedicos();
            break;
        case 3:
            system("cls");
            menuHeader();
            manager.modificarMedicoPorDni();
            break;
        case 4:
            system("cls");
            menuHeader();
            manager.buscarYMostrarMedicoPorDni();
            break;
        case 5:
            system("cls");
            menuHeader();
            managerEsp.cargarEspecialidad();
            break;
        case 6:
            system("cls");
            menuHeader();
            managerEsp.listarEspecialidades();
            break;
        case 7:
            system("cls");
            menuHeader();
            managerEsp.editarEspecialidad();
            break;
        case 8:
            system("cls");
            menuHeader();
            managerEsp.eliminarEspecialidad();
            break;
        case 9:
            system("cls");
            menuHeader();
            managerMedEsp.cargarMedicoEspecialidad();
            break;
        case 10:
            system("cls");
            menuHeader();
            managerMedEsp.eliminarMedicoEspecialidad();
            break;
        case 11:
            system("cls");
            menuHeader();
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

void Menu::menuTurnos()
{
    ManagerTurno manager;
    int opcion;

    do {
        system("cls");
        menuHeader();

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

        switch (opcion)
        {
        case 1:
            manager.sacarTurno();
            break;
        case 2:
            manager.mostrarAgendaSemanal();
            break;
        case 3:
        {
            int id;
            cout << "Ingrese el ID del turno a buscar: ";
            cin >> id;
            break;
        }
        case 4:
            manager.listarTurnos() ;
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

void Menu::menuHeader()
{
    cout << "\n========================================\n";
    cout << "           SISTEMA DE CONSULTORIO        \n";
    cout << "========================================\n";
}

void Menu::menuPrestador()
{
    ManagerPrestador manager;
    int opcion;

    do {
        system("cls");
        menuHeader();
        cout << "\n------------ PRESTADORES ---------------\n";
        cout << "  1) Cargar nuevo prestador\n";
        cout << "  2) Listar prestadores\n";
        cout << "  3) Modificar prestador\n";
        cout << "  4) Dar de baja prestador\n";
        cout << "----------------------------------------\n";
        cout << "  0) Volver al menu principal\n";
        cout << "----------------------------------------\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            system("cls");
            menuHeader();
            manager.cargarNuevoPrestador();
            break;
        case 2:
            system("cls");
            menuHeader();
            manager.listarPrestadores();
            break;
        case 3:
            system("cls");
            menuHeader();
            manager.modificarPrestadorPorId();
            break;
        case 4:
            system("cls");
            menuHeader();
            manager.eliminarPrestadorPorId();
            break;
        case 0:
            cout << "Volviendo al menu principal..." << endl;
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
            cin.ignore();
            cin.get();
        }

        cout << endl;
    }
    while (opcion != 0);
}


void Menu::menuAdministrativo() {
    ManagerAdministrativo managerAdministrativo;  // Instancia local del manager

    int opcion;
    do {
        cout << "\n=========== MENU ADMINISTRATIVO ===========\n";
        cout << "  1) Listar pacientes por especialidad y mes\n";
        cout << "  2) Facturacion mensual\n";
        cout << "  3) Ocupacion medica\n";
        cout << "  4) Turnos cancelados\n";
        cout << "  5) Pacientes atendidos\n";
        cout << "-------------------------------------------\n";
        cout << "  0) Volver al menu principal\n";
        cout << "-------------------------------------------\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            managerAdministrativo.listarPacientesAtendidosPorEspecialidadYMes();
            break;
        case 2:
            managerAdministrativo.obtenerFacturacionDelMes();
            break;
        case 3:
            SubmenuOcupacionMedica(managerAdministrativo);//tengo que pasarlo para acceda a sus metodos
            break;
        case 4:
            SubmenuTurnosCancelados();
            break;
        case 5:
            SubmenuPacientesAtendidos();
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
///desarrollo de submenues

void Menu::SubmenuOcupacionMedica(ManagerAdministrativo& managerAdministrativo) {
    int opcion;
    do {
        cout << "\n---- OCUPACION MEDICA ----\n";
        cout << "  1) Ocupación por día (de un médico)\n";
        cout << "  2) Ocupación por mes (de un médico)\n";
        cout << "  3) Ocupación por especialidad\n";
        cout << "  4) Ocupación total de todos los médicos (en un mes)\n";
        cout << "  0) Volver\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
             managerAdministrativo.ocupacionPorDiaDeMedico();
            break;
        case 2:
             managerAdministrativo.ocupacionPorMesDeMedico();
            break;
        case 3:
            // managerAdministrativo.ocupacionPorEspecialidad();
            break;
        case 4:
            // managerAdministrativo.ocupacionTotalPorMes();
            break;
        case 0:
            break;
        default:
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}

void Menu::SubmenuTurnosCancelados() {
    int opcion;
    do {
        cout << "\n---- TURNOS CANCELADOS ----\n";
        cout << "  1) Cancelaciones por médico en rango de fechas\n";
        cout << "  2) Cancelaciones por especialidad\n";
        cout << "  3) Porcentaje cancelaciones vs. asistencias por mes\n";
        cout << "  0) Volver\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            // managerAdministrativo.cancelacionesPorMedico();
            break;
        case 2:
            // managerAdministrativo.cancelacionesPorEspecialidad();
            break;
        case 3:
            // managerAdministrativo.porcentajeCancelacionesVsAsistencias();
            break;
        case 0:
            break;
        default:
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}

void Menu::SubmenuPacientesAtendidos() {
    int opcion;
    do {
        cout << "\n---- PACIENTES ATENDIDOS ----\n";
        cout << "  1) Por mes y especialidad\n";
        cout << "  2) Por médico\n";
        cout << "  3) Por obra social\n";
        cout << "  0) Volver\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            // managerAdministrativo.atendidosPorMesYEspecialidad();
            break;
        case 2:
            // managerAdministrativo.atendidosPorMedico();
            break;
        case 3:
            // managerAdministrativo.atendidosPorObraSocial();
            break;
        case 0:
            break;
        default:
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}

