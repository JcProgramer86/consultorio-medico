#include "ManagerMedicoEspecialidad.h"
#include "ArchivoMedicoEspecialidad.h"
#include "Menu.h"
#include "ArchivoMedico.h"
#include "ArchivoEspecialidad.h"
#include <iostream>
#include <iomanip>

using namespace std;

void ManagerMedicoEspecialidad::cargarMedicoEspecialidad() {
    system("cls");

    ArchivoMedicoEspecialidad archivo("medicoespecialidades.dat");
    ArchivoMedico archivoMedico("medicos.dat");
    ArchivoEspecialidad archivoEspecialidad("especialidad.dat");

    int nuevoId = archivo.CantidadRegistros() > 0 ?
                  archivo.Leer(archivo.CantidadRegistros() - 1).getId() + 1 : 1;

    cout << "\n===============================================" << endl;
    cout << "        ASIGNAR ESPECIALIDAD A MEDICO          " << endl;
    cout << "===============================================\n" << endl;

    // Mostrar especialidades disponibles
    int cantEsp = archivoEspecialidad.cantidadRegistros();
    cout << "Especialidades disponibles:\n";
    cout << endl;
    cout << left
    << setw(6) << "ID"
    << setw(30) << "Nombre" << endl;

    cout << string(40, '-') << endl;
    for (int i = 0; i < cantEsp; ++i) {
        Especialidad esp = archivoEspecialidad.leer(i);
        if (esp.get_enabled()) {
            cout
            << setw(6) << esp.get_id()
            << setw(30) << esp.get_nombreEspecialidad() << endl;
        }
    }

    int idEspecialidad;
    cout << "\nIngrese el ID de la especialidad: ";
    cin >> idEspecialidad;

    int posEspecialidad = archivoEspecialidad.buscarPorId(idEspecialidad);
    if (posEspecialidad == -1) {
        cout << "\n[!] Especialidad no encontrada." << endl;
        cout << "\nPresione Enter para continuar...";
        cin.ignore();
        cin.get();
        return;
    }

    // Mostrar médicos disponibles
    int cantMed = archivoMedico.CantidadRegistros();
    cout << "\nMedicos disponibles:\n";
    cout << left
         << setw(6)  << "ID"
         << setw(20) << "Nombre"
         << setw(20) << "Apellido"
         << setw(12) << "Matricula"
         << endl;
    cout << string(60, '-') << endl;
    for (int i = 0; i < cantMed; ++i) {
        Medico m = archivoMedico.Leer(i);
        if (m.get_enabled()) {
            cout << setw(6)  << m.get_id()
                 << setw(20) << m.get_nombre()
                 << setw(20) << m.get_apellido()
                 << setw(12) << m.get_matricula()
                 << endl;
        }
    }

    int idMedico;
    cout << "\nIngrese el ID del medico: ";
    cin >> idMedico;

    int posMedico = archivoMedico.Buscar(idMedico);
    if (posMedico == -1) {
        cout << "\n[!] El medico no existe." << endl;
        cout << "\nPresione Enter para continuar...";
        cin.ignore();
        cin.get();
        return;
    }

    // Verificar si ya existe la relación
    int cantidad = archivo.CantidadRegistros();
    for (int i = 0; i < cantidad; ++i) {
        MedicoEspecialidad rel = archivo.Leer(i);
        if (rel.getIdMedico() == idMedico && rel.getIdEspecialidad() == idEspecialidad) {
            cout << "\n[!] Ese medico ya tiene asignada esa especialidad." << endl;
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
            return;
        }
    }

    MedicoEspecialidad nuevaRelacion(nuevoId, idEspecialidad, idMedico);
    cout << "\n-----------------------------------------------" << endl;
    if (archivo.Guardar(nuevaRelacion)) {
        cout << "[OK] Relación medico-especialidad registrada correctamente." << endl;
    } else {
        cout << "[ERROR] No se pudo guardar la relación." << endl;
    }
    cout << "-----------------------------------------------\n" << endl;

    cout << "Presione Enter para continuar...";
    cin.ignore();
    cin.get();
}





void ManagerMedicoEspecialidad::eliminarMedicoEspecialidad() {
    system("cls");
    Menu menu;
    menu.menuHeader();

    ArchivoMedicoEspecialidad archivo("medicoespecialidades.dat");

    int cantidad = archivo.CantidadRegistros();

    cout << "\n=================================================" << endl;
    cout << "        ELIMINAR RELACION MEDICO - ESPECIALIDAD  " << endl;
    cout << "=================================================\n" << endl;

    if (cantidad == 0) {
        cout << "[!] No hay relaciones registradas.\n";
        cout << "\nPresione Enter para continuar...";
        cin.ignore();
        cin.get();
        return;
    }

    // Reutilizamos el método de listar sin encabezado
    listarMedicoEspecialidad(false);

    // Pedir ID a eliminar
    int id;
    cout << "\nIngrese el ID de la relación a eliminar: ";
    cin >> id;

    int pos = archivo.Buscar(id);
    if (pos == -1) {
        cout << "\n[!] No existe la relación con ese ID.\n";
    } else {
        int total = archivo.CantidadRegistros();
        MedicoEspecialidad* todas = new MedicoEspecialidad[total];
        archivo.Leer(total, todas);

        FILE* pArchivo = fopen("medicoespecialidades.dat", "wb");
        for (int i = 0; i < total; ++i) {
            if (todas[i].getId() != id) {
                fwrite(&todas[i], sizeof(MedicoEspecialidad), 1, pArchivo);
            }
        }
        fclose(pArchivo);
        delete[] todas;

        cout << "\n[OK] Relación eliminada correctamente.\n";
    }

    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
}



void ManagerMedicoEspecialidad::listarMedicoEspecialidad(bool titulo) {
    system("cls");
    Menu menu;
    menu.menuHeader();
    ArchivoMedicoEspecialidad archivo("medicoespecialidades.dat");
    ArchivoMedico archivoMedico("medicos.dat");
    ArchivoEspecialidad archivoEspecialidad("especialidad.dat");

    int cantidad = archivo.CantidadRegistros();
    if(titulo){
    cout << "\n=================================================" << endl;
    cout << "           LISTADO MEDICO - ESPECIALIDAD        " << endl;
    cout << "=================================================" << endl;
    cout <<endl;
    }

    if (cantidad == 0) {
        cout << "No hay relaciones medico-especialidad registradas.\n";
    } else {
        cout << left
             << setw(6)  << "ID"
             << setw(12) << "ID Medico"
             << setw(25) << "Nombre Medico"
             << setw(15) << "ID Esp"
             << setw(25) << "Especialidad"
             << endl;
        cout << string(85, '-') << endl;

        for (int i = 0; i < cantidad; ++i) {
            MedicoEspecialidad reg = archivo.Leer(i);

            int posMed = archivoMedico.Buscar(reg.getIdMedico());
            int posEsp = archivoEspecialidad.buscarPorId(reg.getIdEspecialidad());

            string nombreMedico = (posMed != -1) ? archivoMedico.Leer(posMed).get_nombre() : "Desconocido";
            string nombreEspecialidad = (posEsp != -1) ? archivoEspecialidad.leer(posEsp).get_nombreEspecialidad() : "Desconocida";

            cout << left
                 << setw(6)  << reg.getId()
                 << setw(12) << reg.getIdMedico()
                 << setw(25) << nombreMedico
                 << setw(15) << reg.getIdEspecialidad()
                 << setw(25) << nombreEspecialidad
                 << endl;
        }

        cout << string(85, '-') << endl;
    }
    if(titulo){
    cout << "\nPresione Enter para volver al menu...";
    cin.ignore();
    cin.get();
    }
}


void ManagerMedicoEspecialidad::buscarPorIdMedico() {
    ArchivoMedicoEspecialidad archivo("medicoespecialidades.dat");
    int idMedico;
    std::cout << "Ingrese el ID del medico: ";
    std::cin >> idMedico;

    int cantidad = archivo.CantidadRegistros();
    bool encontrado = false;
    for (int i = 0; i < cantidad; i++) {
        MedicoEspecialidad reg = archivo.Leer(i);
        if (reg.getIdMedico() == idMedico) {
            std::cout << "ID Relacion: " << reg.getId()
                      << " | ID Especialidad: " << reg.getIdEspecialidad() << std::endl;
            encontrado = true;
        }
    }
    if (!encontrado) std::cout << "El medico no tiene especialidades registradas.\n";
}

void ManagerMedicoEspecialidad::buscarPorIdEspecialidad() {
    ArchivoMedicoEspecialidad archivo("medicoespecialidades.dat");
    int idEspecialidad;
    std::cout << "Ingrese el ID de la especialidad: ";
    std::cin >> idEspecialidad;

    int cantidad = archivo.CantidadRegistros();
    bool encontrado = false;
    for (int i = 0; i < cantidad; i++) {
        MedicoEspecialidad reg = archivo.Leer(i);
        if (reg.getIdEspecialidad() == idEspecialidad) {
            std::cout << "ID Relacion: " << reg.getId()
                      << " | ID Medico: " << reg.getIdMedico() << std::endl;
            encontrado = true;
        }
    }
    if (!encontrado) std::cout << "No hay médicos con esa especialidad registrada.\n";
}
