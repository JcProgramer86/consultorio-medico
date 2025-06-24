#include <iostream>
#include <iomanip>
#include "Medico.h"
#include "Fecha.h"
#include "ManagerMedico.h"
#include "ArchivoMedico.h"
#include "ManagerEspecialidad.h"
#include "ArchivoEspecialidad.h"
#include "Menu.h"

using namespace std;

extern Menu menu;
void ManagerMedico::registrarNuevoMedico()
{
    system("cls");
    menu.menuHeader();
    cout << "\n========================================" << endl;
    cout << "           ALTA DE NUEVO MEDICO         " << endl;
    cout << "========================================" << endl;

    Medico medico;
    ArchivoMedico aMedico("medicos.dat");
    ArchivoMedicoEspecialidad archivoRel("medicoespecialidades.dat");
    ManagerEspecialidad managerEsp;

    int id, idEspecialidad = 0;
    string dni, nombre, apellido, telefono, email, matricula;

    // --- DNI ---
    do {
        cout << "\nIngrese el numero de DNI (0 para cancelar): ";
        cin >> dni;
        if (dni == "0") {
            cout << "\n[!] Registro cancelado." << endl;
            return;
        }
        if (!medico.validarDNI(dni)) {
            cout << "[!] El DNI ingresado es erroneo." << endl;
            continue;
        }
        if (!aMedico.checkDni(dni)) {
            cout << "[!] El DNI ya esta registrado para otro medico." << endl;
            continue;
        }
        break;
    } while (true);

    cout << "Ingrese el nombre del medico: ";
    cin.ignore();
    getline(cin, nombre);
    while (!Persona::validarTexto(nombre)) {
        cout << "[!] El nombre solo debe contener letras. Intente nuevamente: ";
        getline(cin, nombre);
    }

    cout << "Ingrese el apellido del medico: ";
    getline(cin, apellido);
    while (!Persona::validarTexto(apellido)) {
        cout << "[!] El apellido solo debe contener letras. Intente nuevamente: ";
        getline(cin, apellido);
    }

    cout << "Ingrese el numero de telefono: ";
    getline(cin, telefono);
    while (!medico.validarTelefono(telefono)) {
        cout << "El telefono ingresado es incorrecto" << endl;
        cout << "Ingrese el numero de telefono: ";
        getline(cin, telefono);
    }

    cout << "Ingrese el email: ";
    getline(cin, email);
    while (!medico.validarEmail(email)) {
        cout << "El email ingresado es incorrecto" << endl;
        cout << "Ingrese el email: ";
        getline(cin, email);
    }

    cout << "Ingrese la matricula del medico: ";
    getline(cin, matricula);

    cout << "\n--------------------------------------" << endl;
    cout << "LISTADO DE ESPECIALIDADES DISPONIBLES:" << endl << endl;
    managerEsp.listarEspecialidades(false);
    cout << "--------------------------------------" << endl;
    cout << "Ingrese el ID de especialidad del medico: ";
    cin >> idEspecialidad;

    Fecha fechaNacimiento = Fecha::leerFechaValida("Ingrese la fecha de nacimiento (dd/mm/aaaa): ", true, false);

    Fecha fechaInicioActividad = Fecha::leerFechaValida("Ingrese el inicio de actividad (dd/mm/aaaa): ", false, true);

    bool enabled = true;
    id = aMedico.generarNuevoId();

    medico = Medico(id, dni, nombre, apellido, telefono, email,
                    fechaNacimiento, idEspecialidad, fechaInicioActividad,
                    matricula, enabled);

    cout << "\n--------------------------------------" << endl;
    if (aMedico.Guardar(medico)) {
        cout << "[OK] Medico guardado correctamente." << endl;

        int nuevoIdRelacion = archivoRel.CantidadRegistros() > 0 ?
                              archivoRel.Leer(archivoRel.CantidadRegistros() - 1).getId() + 1 : 1;

        MedicoEspecialidad nuevaRelacion(nuevoIdRelacion, idEspecialidad, id);
        if (archivoRel.Guardar(nuevaRelacion)) {
            cout << "[OK] Relación medico-especialidad registrada correctamente." << endl;
        } else {
            cout << "[ERROR] No se pudo guardar la relación medico-especialidad." << endl;
        }

    } else {
        cout << "[ERROR] Hubo un problema inesperado. Contacte a sistemas." << endl;
    }
    cout << "--------------------------------------\n" << endl;

    cout << "Presione Enter para continuar...";
    cin.ignore();
    cin.get();
}



void ManagerMedico::buscarYMostrarMedicoPorDni()
{
    string dni;
    cout << "Ingrese el DNI del medico a buscar: ";
    cin >> dni;

    ArchivoMedico aMedico("medicos.dat");
    int posicion = aMedico.BuscarPorDni(dni);

    if (posicion != -1)
    {
        system("cls");
        menu.menuHeader();

        Medico medicoEncontrado = aMedico.Leer(posicion);
        ArchivoEspecialidad archivoEsp("especialidad.dat");

        cout << "\n==============================================================" << endl;
        cout << "                  RESULTADO DE LA BUSQUEDA                    " << endl;
        cout << "==============================================================" << endl << endl;

        // Encabezado de columnas
        cout << left
             << setw(4)  << "|ID"
             << setw(12) << "|DNI"
             << setw(15) << "|Nombre"
             << setw(15) << "|Apellido"
             << setw(15) << "|Telefono"
             << setw(25) << "|Email"
             << setw(8)  << "|Matri."
             << setw(12) << "|F.Nac."
             << setw(15) << "|Esp."
             << setw(12) << "|Inicio Act."
             << endl;
        cout << string(135, '-') << endl;

        cout << left
             << setw(4)  << medicoEncontrado.get_id()
             << setw(12) << medicoEncontrado.get_dni()
             << setw(15) << medicoEncontrado.get_nombre()
             << setw(15) << medicoEncontrado.get_apellido()
             << setw(15) << medicoEncontrado.get_telefono()
             << setw(25) << medicoEncontrado.get_email()
             << setw(8)  << medicoEncontrado.get_matricula()
             << setw(12) << medicoEncontrado.get_fechaNacimiento().toString()
             << setw(15) << archivoEsp.leer(medicoEncontrado.get_idEspecialidad()).get_nombreEspecialidad()
             << setw(12) << medicoEncontrado.get_fechaInicioActividad().toString()
             << endl;

        cout << string(135, '=') << endl;
    }
    else
    {
        cout << "\n[!] No se encontro un medico con ese DNI." << endl;
    }

    cout << "\nPresione Enter para volver al menu de Medicos...";
    cin.ignore();
    cin.get();
}


void ManagerMedico::modificarMedicoPorDni() {
    system("cls");
    menu.menuHeader();
    ArchivoMedico aMedico("medicos.dat");
    string dni;

    cout << "\n========================================" << endl;
    cout << "          EDICION DE MEDICO             " << endl;
    cout << "========================================" << endl;
    cout << "Ingrese el DNI del medico a editar: ";
    cin >> dni;

    int pos = aMedico.BuscarPorDni(dni);
    if (pos == -1) {
        cout << "\n[!] Medico no encontrado." << endl;
        return;
    }

    Medico medico = aMedico.Leer(pos);
    int opcion = 0;

    do {
        cout << "\n--- EDICION MEDICO ID: " << medico.get_id() << " ---" << endl;
        cout << "1. Editar DNI           (actual: " << medico.get_dni() << ")" << endl;
        cout << "2. Editar nombre        (actual: " << medico.get_nombre() << ")" << endl;
        cout << "3. Editar apellido      (actual: " << medico.get_apellido() << ")" << endl;
        cout << "4. Editar telefono      (actual: " << medico.get_telefono() << ")" << endl;
        cout << "5. Editar email         (actual: " << medico.get_email() << ")" << endl;
        cout << "6. Editar fecha nac.    (actual: " << medico.get_fechaNacimiento().toString() << ")" << endl;
        cout << "7. Editar id especial.  (actual: " << medico.get_idEspecialidad() << ")" << endl;
        cout << "8. Editar fecha inicio  (actual: " << medico.get_fechaInicioActividad().toString() << ")" << endl;
        cout << "9. Editar matricula     (actual: " << medico.get_matricula() << ")" << endl;
        cout << "10. Editar estado       (actual: " << (medico.get_enabled() ? "Activo" : "Inactivo") << ")" << endl;
        cout << "11. Guardar y salir" << endl;
        cout << "0. Cancelar sin guardar" << endl;
        cout << "--------------------------------------" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
            case 1: {
                string nuevoDni;
                cout << "Ingrese nuevo DNI: ";
                getline(cin, nuevoDni);
                if (aMedico.checkDni(nuevoDni)) {
                    medico.set_dni(nuevoDni);
                } else {
                    cout << "[!] El DNI ya existe o no es valido." << endl;
                }
                break;
            }
            case 2: {
                string nombre;
                cout << "Ingrese nuevo nombre: ";
                getline(cin, nombre);
                medico.set_nombre(nombre);
                break;
            }
            case 3: {
                string apellido;
                cout << "Ingrese nuevo apellido: ";
                getline(cin, apellido);
                medico.set_apellido(apellido);
                break;
            }
            case 4: {
                string telefono;
                cout << "Ingrese nuevo telefono: ";
                getline(cin, telefono);
                medico.set_telefono(telefono);
                break;
            }
            case 5: {
                string email;
                cout << "Ingrese nuevo email: ";
                getline(cin, email);
                medico.set_email(email);
                break;
            }
            case 6: {
                int dia, mes, anio;
                cout << "Ingrese nuevo dia de nacimiento: ";
                cin >> dia;
                cout << "Ingrese nuevo mes: ";
                cin >> mes;
                cout << "Ingrese nuevo anio: ";
                cin >> anio;
                medico.set_fechaNacimiento(Fecha(dia, mes, anio));
                cin.ignore();
                break;
            }
            case 7: {
                int idEspecialidad;
                cout << "Ingrese nuevo id de especialidad: ";
                cin >> idEspecialidad;
                medico.set_idEspecialidad(idEspecialidad);
                cin.ignore();
                break;
            }
            case 8: {
                int dia, mes, anio;
                cout << "Ingrese nuevo dia de inicio: ";
                cin >> dia;
                cout << "Ingrese nuevo mes: ";
                cin >> mes;
                cout << "Ingrese nuevo anio: ";
                cin >> anio;
                medico.set_fechaInicioActividad(Fecha(dia, mes, anio));
                cin.ignore();
                break;
            }
            case 9: {
                string matricula;
                cout << "Ingrese nueva matricula: ";
                getline(cin, matricula);
                medico.set_matricula(matricula);
                break;
            }
            case 10: {
                int estado;
                cout << "Ingrese nuevo estado (1=activo, 0=inactivo): ";
                cin >> estado;
                medico.set_enabled(estado == 1);
                cin.ignore();
                break;
            }
            case 11:
                cout << "\n--------------------------------------" << endl;
                if (aMedico.Guardar(medico, pos)) {
                    cout << "[OK] Medico actualizado correctamente." << endl;
                } else {
                    cout << "[ERROR] No se pudo guardar el medico." << endl;
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


void ManagerMedico::listarMedicos()
{
    system("cls");
    menu.menuHeader();
    cout << "\n==============================================================" << endl;
    cout << "                    LISTADO DE MEDICOS ACTIVOS                " << endl;
    cout << "==============================================================" << endl;
    cout << endl;

    ArchivoMedico archivo("medicos.dat");
    ArchivoMedicoEspecialidad archivoRel("medicoespecialidades.dat");
    ArchivoEspecialidad archivoEsp("especialidad.dat");

    int cantidad = archivo.CantidadRegistros();

    if (cantidad == 0)
    {
        cout << "\nNo hay medicos cargados." << endl << endl;
        return;
    }

    cout << left
         << setw(4)  << "|ID"
         << setw(12) << "|DNI"
         << setw(15) << "|Nombre"
         << setw(15) << "|Apellido"
         << setw(15) << "|Telefono"
         << setw(25) << "|Email"
         << setw(8)  << "|Matri."
         << setw(12) << "|F.Nac."
         << setw(30) << "|Esp." // ancho mayor
         << setw(12) << "|Inicio Act."
         << endl;
    cout << string(156, '-') << endl;

    bool hayActivos = false;

    for (int i = 0; i < cantidad; i++)
    {
        Medico medico = archivo.Leer(i);

        if (medico.get_enabled())
        {
            hayActivos = true;

            // Arreglo para guardar los nombres
            char especialidades[10][100];
            int cantEsp = 0;

            int totalRel = archivoRel.CantidadRegistros();

            for (int j = 0; j < totalRel; ++j)
            {
                MedicoEspecialidad rel = archivoRel.Leer(j);
                if (rel.getIdMedico() == medico.get_id() && cantEsp < 10)
                {
                    int posEsp = archivoEsp.buscarPorId(rel.getIdEspecialidad());
                    if (posEsp >= 0)
                    {
                        Especialidad esp = archivoEsp.leer(posEsp);
                        strcpy(especialidades[cantEsp], esp.get_nombreEspecialidad());
                        cantEsp++;
                    }
                }
            }

            // Concatenar nombres
            char nombresConcatenados[300] = "";
            for (int k = 0; k < cantEsp; k++)
            {
                strcat(nombresConcatenados, especialidades[k]);
                if (k != cantEsp - 1)
                {
                    strcat(nombresConcatenados, ",");
                }
            }

            // Mostrar
            cout << left
                 << setw(4)  << medico.get_id()
                 << setw(12) << medico.get_dni()
                 << setw(15) << medico.get_nombre()
                 << setw(15) << medico.get_apellido()
                 << setw(15) << medico.get_telefono()
                 << setw(25) << medico.get_email()
                 << setw(8)  << medico.get_matricula()
                 << setw(12) << medico.get_fechaNacimiento().toString()
                 << setw(30) << nombresConcatenados
                 << setw(12) << medico.get_fechaInicioActividad().toString()
                 << endl;
        }
    }

    cout << string(156, '=') << endl << endl;

    if (!hayActivos)
    {
        cout << "No hay medicos activos para mostrar." << endl << endl;
    }

    cout << "\nPresione Enter para volver al menu de Medicos...";
    cin.ignore();
    cin.get();
}
