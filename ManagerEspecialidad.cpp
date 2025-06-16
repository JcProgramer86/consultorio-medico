#include "ManagerEspecialidad.h"
#include <iostream>
#include <cstring>
#include <iomanip>
#include <string>

using namespace std;

void ManagerEspecialidad::cargarEspecialidad() {
    ArchivoEspecialidad archivo("especialidad.dat");
    Especialidad especialidad;

    int nuevoId = archivo.cantidadRegistros() > 0
                  ? archivo.leer(archivo.cantidadRegistros() - 1).get_id() + 1
                  : 1;
    especialidad.set_id(nuevoId);

    char codigo[10];
    char nombre[100];

    cout << "Ingrese codigo de especialidad: ";
    cin.ignore();
    cin.getline(codigo, 10);
    especialidad.set_codEspecialidad(codigo);

    cout << "Ingrese nombre de especialidad: ";
    cin.getline(nombre, 100);
    especialidad.set_nombreEspecialidad(nombre);

    if (archivo.guardar(especialidad)) {
        cout << "Especialidad cargada correctamente." << endl;
    } else {
        cout << "Error al guardar la especialidad." << endl;
    }
}

void ManagerEspecialidad::editarEspecialidad() {
    ArchivoEspecialidad archivo("especialidad.dat");
    ArchivoMedicoEspecialidad archivoMedEsp("medico_especialidad.dat");

    int id;
    cout << "Ingrese el ID de la especialidad a editar: ";
    cin >> id;

    int pos = archivo.buscarPorId(id);
    if (pos == -1) {
        cout << "Especialidad no encontrada." << endl;
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
        cout << "Atencion: hay medicos asociados a esta especialidad." << endl;
    }

    Especialidad esp = archivo.leer(pos);

    char cod[10], nombre[100];
    cout << "Codigo actual: " << esp.get_codEspecialidad() << ". Nuevo (dejar vacio para no cambiar): ";
    cin.ignore();
    cin.getline(cod, 10);
    if (strlen(cod) > 0) esp.set_codEspecialidad(cod);

    cout << "Nombre actual: " << esp.get_nombreEspecialidad() << ". Nuevo (dejar vacio para no cambiar): ";
    cin.getline(nombre, 100);
    if (strlen(nombre) > 0) esp.set_nombreEspecialidad(nombre);

    if (archivo.guardar(esp, pos)) {
        cout << "Especialidad actualizada correctamente." << endl;
    } else {
        cout << "Error al actualizar la especialidad." << endl;
    }
}

void ManagerEspecialidad::eliminarEspecialidad() {
    ArchivoEspecialidad archivo("especialidad.dat");
    ArchivoMedicoEspecialidad archivoMedEsp("medico_especialidad.dat");

    int id;
    cout << "Ingrese el ID de la especialidad a eliminar: ";
    cin >> id;

    int pos = archivo.buscarPorId(id);
    if (pos == -1) {
        cout << "Especialidad no encontrada." << endl;
        return;
    }

    int totalMedEsp = archivoMedEsp.CantidadRegistros();
    for (int i = 0; i < totalMedEsp; ++i) {
        MedicoEspecialidad medEsp = archivoMedEsp.Leer(i);
        if (medEsp.getIdEspecialidad() == id) {
            cout << "No se puede eliminar: la especialidad esta asociada a medicos." << endl;
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
    cout << "Especialidad eliminada correctamente." << endl;
}

void ManagerEspecialidad::listarEspecialidades() {
    ArchivoEspecialidad archivo("especialidad.dat");
    int cantidad = archivo.cantidadRegistros();

    if (cantidad == 0) {
        cout << "No hay especialidades registradas." << endl;
        return;
    }

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
