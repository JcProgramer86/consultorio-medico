#include "ManagerPaciente.h"
#include "Paciente.h"
#include "ArchivoPaciente.h"
#include "ArchivoPrestador.h"
#include "Fecha.h"
#include <iostream>
#include <iomanip>
#include "Menu.h"

using namespace std;

Menu menu;

void ManagerPaciente::crearNuevoPaciente() {
    system("cls");
    menu.menuHeader();

    Paciente paciente;
    ArchivoPaciente aPaciente("paciente.dat") ;
    ArchivoPrestador archivoPrestador("prestadores.dat");


    string nombre, apellido, dni, telefono, email;
    int idPrestador, id;
    int cantidadPrestadores = archivoPrestador.CantidadRegistros();

    if (cantidadPrestadores == 0) {
        cout << "\n[!] Para poder crear un paciente debe existir al menos un prestador cargado." << endl;
        cout << "Presione Enter para volver al menú de pacientes...";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "\n========================================" << endl;
    cout << "          ALTA DE NUEVO PACIENTE        " << endl;
    cout << "========================================" << endl;

    do {
        cout << "\nIngrese el numero de DNI (0 para cancelar): ";
        cin >> dni;
        if (dni == "0") {
            cout << "\n[!] Registro cancelado." << endl;
            return;
        }
        if (!paciente.validarDNI(dni)) {
            cout << "[!] El DNI ingresado es erroneo." << endl;
            continue;
        }
        if (!aPaciente.checkDni(dni)) {
            cout << "[!] El DNI ya está registrado para otro paciente." << endl;
            continue;
        }
        break;
    } while (true);

    cout << "Ingrese el nombre del paciente: ";
    cin.ignore();
    getline(cin, nombre);
    while (!Paciente::validarTexto(nombre)) {
    cout << "[!] El nombre solo debe contener letras. Intente nuevamente: ";
    getline(cin, nombre);
}

    cout << "Ingrese el apellido del paciente: ";
    getline(cin, apellido);
    while (!Paciente::validarTexto(apellido)) {
    cout << "[!] El apellido solo debe contener letras. Intente nuevamente: ";
    getline(cin, apellido);
}

    cout << "Ingrese el numero de telefono: ";
    getline(cin, telefono);
    while (!paciente.validarTelefono(telefono)) {
        cout << "El telefono ingresado es incorrecto." << endl;
        cout << "Ingrese el numero de telefono: ";
        getline(cin, telefono);
    }

    cout << "Ingrese el email: ";
    getline(cin, email);
    while (!paciente.validarEmail(email)) {
        cout << "El email ingresado es incorrecto." << endl;
        cout << "Ingrese el email: ";
        getline(cin, email);
    }

    Fecha fechaNacimiento = Fecha::leerFechaValida("Ingrese la fecha de nacimiento (dd/mm/aaaa): ", true, false);

    cout << "\n--------------------------------------" << endl;
    cout << "LISTADO DE PRESTADORES DISPONIBLES:\n" << endl;

    cout << left << setw(5) << "ID" << setw(30) << "Nombre" << endl;
    cout << string(35, '-') << endl;

    for(int i = 0; i < cantidadPrestadores; ++i) {
        Prestador p = archivoPrestador.Leer(i);
        cout << left << setw(5) << p.getId() << setw(30) << p.getNombrePrestador() << endl;
    }
    cout << string(35, '-') << endl;


    bool idValido = false;
    do {
        cout << "Ingrese el ID del prestador: ";
        cin >> idPrestador;

        idValido = false;
        for(int i = 0; i < cantidadPrestadores; ++i) {
            Prestador p = archivoPrestador.Leer(i);
            if(p.getId() == idPrestador) {
                idValido = true;
                break;
            }
        }
        if(!idValido) {
            cout << "[!] ID de prestador no válido. Seleccione uno de la lista." << endl;
        }
    } while(!idValido);

    id = aPaciente.generarNuevoId();

    paciente = Paciente(id, dni, nombre, apellido, telefono, email, idPrestador, fechaNacimiento);

    cout << "\n--------------------------------------" << endl;
    if(aPaciente.Guardar(paciente)){
        cout << "[OK] Paciente guardado correctamente." << endl;
        cout << "Presione Enter para continuar...";
        cin.ignore();
        cin.get();
    } else {
        cout << "[ERROR] Ocurrio un problema inesperado. Contacte a sistemas." << endl;
    }
    cout << "--------------------------------------\n" << endl;
}



void ManagerPaciente::ListarTodos(){
    system("cls");
    menu.menuHeader();

    Paciente paciente;
    ArchivoPrestador aPrestador("prestadores.dat");
    ArchivoPaciente aPaciente("paciente.dat");
    int cant = aPaciente.CantidadRegistros();

    cout << "\n==============================================================" << endl;
    cout << "                  LISTADO DE PACIENTES ACTIVOS                " << endl;
    cout << "==============================================================" << endl;
    cout << endl;

    if (cant == 0) {
        cout << "\nNo hay pacientes registrados." << endl;
        return;
    }

    // Encabezado de columnas (sin la columna Activo)
    cout << left
         << setw(4)  << "|ID"
         << setw(12) << "|Documento"
         << setw(15) << "|Nombre"
         << setw(15) << "|Apellido"
         << setw(15) << "|Telefono"
         << setw(35) << "|Email"
         << setw(12) << "|F.Nac."
         << setw(10) << "|Prestador"
         << endl;

    cout << string(130, '-') << endl;

    // Filtrar e imprimir solo los activos
    int encontrados = 0;
    for(int x = 0; x < cant; x++){
        paciente = aPaciente.Leer(x);

        if (!paciente.get_enabled()) {
            continue; // Salta los inactivos
        }
        encontrados++;

        int idPrestador = paciente.get_idPrestador();
        std::string nombrePrestador = "N/A";

        int cantPrestadores = aPrestador.CantidadRegistros();
        for (int i = 0; i < cantPrestadores; i++) {
            Prestador prestador = aPrestador.Leer(i);
            if (prestador.getId() == idPrestador) {
                nombrePrestador = prestador.getNombrePrestador();
                break;
            }
        }

        cout << left
             << setw(4)  << paciente.get_id()
             << setw(12) << paciente.get_dni()
             << setw(15) << paciente.get_nombre()
             << setw(15) << paciente.get_apellido()
             << setw(15) << paciente.get_telefono()
             << setw(35) << paciente.get_email()
             << setw(12) << paciente.get_fechaNacimiento().toString()
             << setw(10) << nombrePrestador
             << endl;
    }

    cout << string(130, '=') << endl << endl;
    if (encontrados == 0) {
        cout << "No hay pacientes activos para mostrar." << endl << endl;
    }

    cout << "Presione Enter para continuar...";
    cin.ignore();
    cin.get();
}


void ManagerPaciente::MostrarPorDni(){
    system("cls");
    menu.menuHeader();

    Paciente paciente;
    ArchivoPaciente aPaciente("paciente.dat");
    string dni;

    cout << "\n======================================" << endl;
    cout << "       BUSQUEDA DE PACIENTE POR DNI    " << endl;
    cout << "======================================" << endl;
    cout << "Ingrese el documento del paciente a buscar: ";
    cin >> dni;

    int posPaciente = aPaciente.BuscarPorDni(dni);

    if (posPaciente == -1) {
        cout << "\n[!] Paciente no encontrado." << endl;
        return;
    }

    paciente = aPaciente.Leer(posPaciente);

    cout << "\n------------- DATOS DEL PACIENTE -------------" << endl<<endl;
    cout << "ID: " << paciente.get_id() << endl;
    cout << "Documento: " << paciente.get_dni() << endl;
    cout << "Nombre: " << paciente.get_nombre() << endl;
    cout << "Apellido: " << paciente.get_apellido() << endl;
    cout << "Telefono: " << paciente.get_telefono() << endl;
    cout << "Email: " << paciente.get_email() << endl;
    cout << "Fecha de nacimiento: " << paciente.get_fechaNacimiento().toString() << endl;
    cout << "ID del prestador: " << paciente.get_idPrestador() << endl;
    cout << "Habilitado" << paciente.get_enabled() << endl;
    cout << "----------------------------------------------\n" << endl;

    cout << "Presione Enter para volver al menu...";
    cin.ignore();
    cin.get();
}

void ManagerPaciente::EditarPaciente() {
    system("cls");
    menu.menuHeader();

    ArchivoPaciente aPaciente("paciente.dat");
    string dni;

    cout << "\n======================================" << endl;
    cout << "         EDICION DE PACIENTE          " << endl;
    cout << "======================================" << endl;
    cout << "Ingrese el documento del paciente a editar: ";
    cin >> dni;

    int pos = aPaciente.BuscarPorDni(dni);
    if (pos == -1) {
        cout << "\n[!] Paciente no encontrado." << endl;
        return;
    }

    Paciente paciente = aPaciente.Leer(pos);
    int opcion = 0;

    do {
        cout << "\n--- EDICION PACIENTE ID: " << paciente.get_id() << " ---" << endl;
        cout << "1. Editar nombre       (actual: " << paciente.get_nombre() << ")" << endl;
        cout << "2. Editar apellido     (actual: " << paciente.get_apellido() << ")" << endl;
        cout << "3. Editar telefono     (actual: " << paciente.get_telefono() << ")" << endl;
        cout << "4. Editar email        (actual: " << paciente.get_email() << ")" << endl;
        cout << "5. Editar fecha nac.   (actual: " << paciente.get_fechaNacimiento().toString() << ")" << endl;
        cout << "6. Editar ID prestador (actual: " << paciente.get_idPrestador() << ")" << endl;
        cout << "7. Guardar y salir" << endl;
        cout << "0. Cancelar sin guardar" << endl;
        cout << "--------------------------------------" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
            case 1: {
                string nombre;
                cout << "Ingrese nuevo nombre: ";
                getline(cin, nombre);
                paciente.set_nombre(nombre);
                break;
            }
            case 2: {
                string apellido;
                cout << "Ingrese nuevo apellido: ";
                getline(cin, apellido);
                paciente.set_apellido(apellido);
                break;
            }
            case 3: {
                string telefono;
                cout << "Ingrese nuevo telefono: ";
                getline(cin, telefono);
                paciente.set_telefono(telefono);
                break;
            }
            case 4: {
                string email;
                cout << "Ingrese nuevo email: ";
                getline(cin, email);
                paciente.set_email(email);
                break;
            }
            case 5: {
                int dia, mes, anio;
                cout << "Ingrese nuevo dia de nacimiento: ";
                cin >> dia;
                cout << "Ingrese nuevo mes: ";
                cin >> mes;
                cout << "Ingrese nuevo anio: ";
                cin >> anio;
                paciente.set_fechaNacimiento(Fecha(dia, mes, anio));
                break;
            }
            case 6: {
                int idPrestador;
                cout << "Ingrese nuevo ID de prestador: ";
                cin >> idPrestador;
                paciente.set_idPrestador(idPrestador);
                break;
            }
            case 7:
                cout << "\n--------------------------------------" << endl;
                if (aPaciente.Guardar(paciente, pos)) {
                    cout << "[OK] Paciente actualizado correctamente." << endl;
                } else {
                    cout << "[ERROR] No se pudo guardar el paciente." << endl;
                }
                cout << "--------------------------------------\n" << endl;
                return;
            case 0:
                cout << "\nOperacion cancelada. No se realizaron cambios." << endl;
                return;
            default:
                cout << "\nOpcion invalida. Intente nuevamente." << endl;
        }
    } while (true);
}
