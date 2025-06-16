#include "ManagerEspecialidad.h"
#include <iostream>
#include <cstring>
#include <iomanip>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;

void ManagerEspecialidad::cargarEspecialidad() {
    system("cls");
    ArchivoEspecialidad archivo("especialidad.dat");
    Especialidad especialidad;

    int nuevoId = archivo.cantidadRegistros() > 0
                  ? archivo.leer(archivo.cantidadRegistros() - 1).get_id() + 1
                  : 1;
    especialidad.set_id(nuevoId);

    std::string codigo;
    std::string  nombre;

    cout << "\n========================================" << endl;
    cout << "         CARGA DE ESPECIALIDAD          " << endl;
    cout << "========================================" << endl;

    cout << "Ingrese nombre de especialidad: ";
    cin.ignore();
    getline(cin, nombre);
    especialidad.set_nombreEspecialidad(nombre);

    codigo = especialidad.generarCodigoEspecialidad(nombre,nuevoId);

    cout << "El codigo de especialidad asignado es: "<<codigo<<endl;

    especialidad.set_codEspecialidad(codigo);



    cout << "\n--------------------------------------" << endl;
    if (archivo.guardar(especialidad)) {
        cout << "[OK] Especialidad cargada correctamente." << endl;
    } else {
        cout << "[ERROR] No se pudo guardar la especialidad." << endl;
    }
    cout << "--------------------------------------\n" << endl;

    cout << "Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}


void ManagerEspecialidad::editarEspecialidad() {
    system("cls");
    ArchivoEspecialidad archivo("especialidad.dat");
    ArchivoMedicoEspecialidad archivoMedEsp("medico_especialidad.dat");

    cout << "\n========================================" << endl;
    cout << "           EDICION DE ESPECIALIDAD      " << endl;
    cout << "========================================" << endl;

    int id;
    listarEspecialidades(false);
    cout << "Ingrese el ID de la especialidad a editar: ";
    cin >> id;

    int pos = archivo.buscarPorId(id);
    if (pos == -1) {
        cout << "\n[!] Especialidad no encontrada." << endl;
        cout << "\nPresione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }

    int totalMedEsp = archivoMedEsp.CantidadRegistros();
    bool asociada = false;
    for (int i = 0; i < totalMedEsp; ++i) {
        MedicoEspecialidad medEsp = archivoMedEsp.Leer(i);
        if (medEsp.getIdEspecialidad() == id) {
            asociada = true;
            break;
        }
    }
    if (asociada) {
        cout << "[!] Atencion: hay medicos asociados a esta especialidad." << endl;
    }

    Especialidad esp = archivo.leer(pos);

    std::string codigo;
    std::string nombre;

    cin.ignore();  // limpiar buffer

    cout << "Nombre actual: " << esp.get_nombreEspecialidad()
         << ". Nuevo (dejar vacio para no cambiar): ";
    getline(cin, nombre);

    std::string sinEspacios = nombre;
    sinEspacios.erase(remove(sinEspacios.begin(), sinEspacios.end(), ' '), sinEspacios.end());

    if (!sinEspacios.empty()) {
        esp.set_nombreEspecialidad(nombre);  // solo un argumento

        // usamos el ID actual de la especialidad para generar el nuevo código
        int idEspecialidad = esp.get_id();
        codigo = esp.generarCodigoEspecialidad(nombre, idEspecialidad);
        esp.set_codEspecialidad(codigo);

        cout << "El nuevo codigo de especialidad asignado es: " << codigo << endl;
    }

    cout << "\n--------------------------------------" << endl;
    if (archivo.guardar(esp, pos)) {
        cout << "[OK] Especialidad actualizada correctamente." << endl;
    } else {
        cout << "[ERROR] No se pudo actualizar la especialidad." << endl;
    }
    cout << "--------------------------------------\n" << endl;

    cout << "Presione Enter para continuar...";
    cin.get();
}

void ManagerEspecialidad::eliminarEspecialidad() {
    system("cls");
    ArchivoEspecialidad archivo("especialidad.dat");
    ArchivoMedicoEspecialidad archivoMedEsp("medico_especialidad.dat");

    cout << "\n========================================" << endl;
    cout << "         ELIMINAR ESPECIALIDAD          " << endl;
    cout << "========================================" << endl;


    int id;
    cout << "Ingrese el ID de la especialidad a eliminar: ";
    cin >> id;

    int pos = archivo.buscarPorId(id);
    if (pos == -1) {
        cout << "\n[!] Especialidad no encontrada." << endl;
        cout << "\nPresione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }

    int totalMedEsp = archivoMedEsp.CantidadRegistros();
    for (int i = 0; i < totalMedEsp; ++i) {
        MedicoEspecialidad medEsp = archivoMedEsp.Leer(i);
        if (medEsp.getIdEspecialidad() == id) {
            cout << "[!] No se puede eliminar: la especialidad esta asociada a medicos." << endl;
            cout << "\nPresione Enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            return;
        }
    }

    int total = archivo.cantidadRegistros();
    Especialidad* todas = new Especialidad[total];
    archivo.leer(total, todas);

    FILE* pArchivo = fopen("especialidad.dat", "wb");
    for (int i = 0; i < total; ++i) {
        if (todas[i].get_id() != id) {
            fwrite(&todas[i], sizeof(Especialidad), 1, pArchivo);
        }
    }
    fclose(pArchivo);
    delete[] todas;

    cout << "\n[OK] Especialidad eliminada correctamente." << endl;

    cout << "\nPresione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void ManagerEspecialidad::listarEspecialidades(bool titulo ) {
    ArchivoEspecialidad archivo("especialidad.dat");
    int cantidad = archivo.cantidadRegistros();

    if(titulo){
    cout << "\n======================================================" << endl;
    cout << "                 LISTADO DE ESPECIALIDADES            " << endl;
    cout << "======================================================" << endl << endl;
    }

    if (cantidad == 0) {
        cout << "No hay especialidades registradas." << endl;
    } else {
        cout << left
             << setw(6)  << "ID"
             << setw(12) << "Codigo"
             << setw(30) << "Nombre"
             << endl;
        cout << string(48, '-') << endl;

        for (int i = 0; i < cantidad; i++) {
            Especialidad esp = archivo.leer(i);
            cout << left
                 << setw(6)  << esp.get_id()
                 << setw(12) << esp.get_codEspecialidad()
                 << setw(30) << esp.get_nombreEspecialidad()
                 << endl;
        }

        cout << string(48, '-') << endl;
    }
    if(titulo){
    cout << "\nPresione Enter para volver al menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    }
}
