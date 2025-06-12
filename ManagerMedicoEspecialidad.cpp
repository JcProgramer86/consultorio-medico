#include "ManagerMedicoEspecialidad.h"
#include "ArchivoMedicoEspecialidad.h"
#include "ArchivoMedico.h"
#include "ArchivoEspecialidad.h"
#include <iostream>
#include <iomanip>

void ManagerMedicoEspecialidad::cargarMedicoEspecialidad() {
    ArchivoMedicoEspecialidad archivo("medicoespecialidades.dat");
    ArchivoMedico archivoMedico("medicos.dat");
    ArchivoEspecialidad archivoEspecialidad("especialidad.dat");

    int nuevoId = archivo.CantidadRegistros() > 0 ?
                  archivo.Leer(archivo.CantidadRegistros() - 1).getId() + 1 : 1;

    // Mostrar especialidades disponibles
    int cantEsp = archivoEspecialidad.cantidadRegistros();
    std::cout << "\nEspecialidades disponibles:\n";
    std::cout << std::left << std::setw(6) << "ID" << std::setw(20) << "Nombre" << "\n";
    std::cout << "-----------------------------\n";
    for (int i = 0; i < cantEsp; ++i) {
        Especialidad esp = archivoEspecialidad.leer(i);
        std::cout << std::setw(6) << esp.get_id() << std::setw(20) << esp.get_nombreEspecialidad() << "\n";
    }

    int idEspecialidad;
    std::cout << "\nIngrese el ID de especialidad: ";
    std::cin >> idEspecialidad;

    int posEspecialidad = archivoEspecialidad.buscarPorId(idEspecialidad);
    if (posEspecialidad == -1) {
        std::cout << "Especialidad no encontrada.\n";
        return;
    }

    // Mostrar médicos disponibles
    int cantMed = archivoMedico.CantidadRegistros();
    std::cout << "\nMédicos disponibles:\n";
    std::cout << std::left << std::setw(6) << "ID"
              << std::setw(20) << "Nombre"
              << std::setw(20) << "Apellido"
              << std::setw(12) << "Matricula" << "\n";
    std::cout << "--------------------------------------------------------\n";
    for (int i = 0; i < cantMed; ++i) {
        Medico m = archivoMedico.Leer(i);
        std::cout << std::setw(6) << m.get_id()
                  << std::setw(20) << m.get_nombre()
                  << std::setw(20) << m.get_apellido()
                  << std::setw(12) << m.get_matricula() << "\n";
    }

    int idMedico;
    std::cout << "\nIngrese el ID del médico: ";
    std::cin >> idMedico;

    int posMedico = archivoMedico.Buscar(idMedico);
    if (posMedico == -1) {
        std::cout << "El medico no existe.\n";
        return;
    }

    // Verificar si ya existe esa relación
    int cantidad = archivo.CantidadRegistros();
    for (int i = 0; i < cantidad; ++i) {
        MedicoEspecialidad rel = archivo.Leer(i);
        if (rel.getIdMedico() == idMedico && rel.getIdEspecialidad() == idEspecialidad) {
            std::cout << "Ese medico ya tiene asignada esa especialidad.\n";
            return;
        }
    }

    MedicoEspecialidad nuevaRelacion(nuevoId, idEspecialidad, idMedico);
    if (archivo.Guardar(nuevaRelacion)) {
        std::cout << "Relacion medico-especialidad registrada correctamente.\n";
    } else {
        std::cout << "Error al guardar la relacion.\n";
    }
}




void ManagerMedicoEspecialidad::eliminarMedicoEspecialidad() {
    ArchivoMedicoEspecialidad archivo("medicoespecialidades.dat");
    int id;
    std::cout << "Ingrese el ID de la relación a eliminar: ";
    std::cin >> id;

    int pos = archivo.Buscar(id);
    if (pos == -1) {
        std::cout << "No existe la relación con ese ID.\n";
        return;
    }

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

    std::cout << "Relacion eliminada correctamente.\n";
}

void ManagerMedicoEspecialidad::listarMedicoEspecialidad() {
    ArchivoMedicoEspecialidad archivo("medicoespecialidades.dat");
    int cantidad = archivo.CantidadRegistros();
    if (cantidad == 0) {
        std::cout << "No hay relaciones medico-especialidad.\n";
        return;
    }

    std::cout << "------ LISTADO DE RELACIONES ------\n";
    for (int i = 0; i < cantidad; i++) {
        MedicoEspecialidad reg = archivo.Leer(i);
        std::cout << "ID Relacion: " << reg.getId()
                  << " | ID Medico: " << reg.getIdMedico()
                  << " | ID Especialidad: " << reg.getIdEspecialidad() << std::endl;
    }
    std::cout << "-----------------------------------\n";
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
