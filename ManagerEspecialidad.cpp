#include "ManagerEspecialidad.h"
#include <iostream>
#include <cstring>
#include <iomanip>
#include <string>


void ManagerEspecialidad::cargarEspecialidad() {
    ArchivoEspecialidad archivo("especialidad.dat");
    Especialidad especialidad;

    // Generar nuevo ID incremental
    int nuevoId = archivo.cantidadRegistros() > 0
                  ? archivo.leer(archivo.cantidadRegistros() - 1).get_id() + 1
                  : 1;
    especialidad.set_id(nuevoId);

    char codigo[10];
    char nombre[100];

    std::cout << "Ingrese código de especialidad: ";
    std::cin.ignore();
    std::cin.getline(codigo, 10);
    especialidad.set_codEspecialidad(codigo);

    std::cout << "Ingrese nombre de especialidad: ";
    std::cin.getline(nombre, 100);
    especialidad.set_nombreEspecialidad(nombre);

    if (archivo.guardar(especialidad)) {
        std::cout << "Especialidad cargada correctamente.\n";
    } else {
        std::cout << "Error al guardar la especialidad.\n";
    }
}

void ManagerEspecialidad::editarEspecialidad() {
    ArchivoEspecialidad archivo("especialidad.dat");
    ArchivoMedicoEspecialidad archivoMedEsp("medico_especialidad.dat");

    int id;
    std::cout << "Ingrese el ID de la especialidad a editar: ";
    std::cin >> id;

    int pos = archivo.buscarPorId(id);
    if (pos == -1) {
        std::cout << "Especialidad no encontrada.\n";
        return;
    }

    // ¿Tiene médicos asociados? (solo advertencia)
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
        std::cout << "⚠️ Advertencia: hay médicos asociados a esta especialidad.\n";
    }

    Especialidad esp = archivo.leer(pos);

    char cod[10], nombre[100];
    std::cout << "Código actual: " << esp.get_codEspecialidad() << ". Nuevo (dejar vacío para no cambiar): ";
    std::cin.ignore();
    std::cin.getline(cod, 10);
    if (strlen(cod) > 0) esp.set_codEspecialidad(cod);

    std::cout << "Nombre actual: " << esp.get_nombreEspecialidad() << ". Nuevo (dejar vacío para no cambiar): ";
    std::cin.getline(nombre, 100);
    if (strlen(nombre) > 0) esp.set_nombreEspecialidad(nombre);

    if (archivo.guardar(esp, pos)) {
        std::cout << "Especialidad actualizada correctamente.\n";
    } else {
        std::cout << "Error al actualizar la especialidad.\n";
    }
}

void ManagerEspecialidad::eliminarEspecialidad() {
    ArchivoEspecialidad archivo("especialidad.dat");
    ArchivoMedicoEspecialidad archivoMedEsp("medico_especialidad.dat");

    int id;
    std::cout << "Ingrese el ID de la especialidad a eliminar: ";
    std::cin >> id;

    int pos = archivo.buscarPorId(id);
    if (pos == -1) {
        std::cout << "Especialidad no encontrada.\n";
        return;
    }

    // Validar que no la use ningún médico
    int totalMedEsp = archivoMedEsp.CantidadRegistros();
    for (int i = 0; i < totalMedEsp; ++i) {
        MedicoEspecialidad medEsp = archivoMedEsp.Leer(i);
        if (medEsp.getIdEspecialidad() == id) {
            std::cout << "❌ No se puede eliminar: la especialidad está asociada a médicos.\n";
            return;
        }
    }

    // Borrado físico reescribiendo el archivo (sin la especialidad eliminada)
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
    std::cout << "Especialidad eliminada correctamente.\n";
}



void ManagerEspecialidad::listarEspecialidades() {
    ArchivoEspecialidad archivo("especialidad.dat");
    int cantidad = archivo.cantidadRegistros();

    if (cantidad == 0) {
        std::cout << "No hay especialidades registradas." << std::endl;
        return;
    }

    std::cout << std::left
              << std::setw(6)  << "ID"
              << std::setw(12) << "Codigo"
              << std::setw(30) << "Nombre"
              << std::endl;
    std::cout << std::string(48, '-') << std::endl;

    for (int i = 0; i < cantidad; i++) {
        Especialidad esp = archivo.leer(i);
        std::cout << std::left
                  << std::setw(6)  << esp.get_id()
                  << std::setw(12) << esp.get_codEspecialidad()
                  << std::setw(30) << esp.get_nombreEspecialidad()
                  << std::endl;
    }
    std::cout << std::string(48, '-') << std::endl;
}

