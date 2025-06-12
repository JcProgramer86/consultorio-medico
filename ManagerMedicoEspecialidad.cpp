#include "ManagerMedicoEspecialidad.h"
#include "ArchivoMedicoEspecialidad.h"
#include "ArchivoMedico.h"
#include "ArchivoEspecialidad.h"
#include <iostream>

void ManagerMedicoEspecialidad::cargarMedicoEspecialidad() {
    ArchivoMedicoEspecialidad archivo("medico_especialidad.dat");
    ArchivoMedico archivoMedico("medico.dat");
    ArchivoEspecialidad archivoEspecialidad("especialidad.dat");

    int nuevoId = archivo.CantidadRegistros() > 0 ?
                  archivo.Leer(archivo.CantidadRegistros() - 1).getId() + 1 : 1;

    int idMedico, idEspecialidad;

    std::cout << "ID de medico: ";
    std::cin >> idMedico;
    std::cout << "ID de especialidad: ";
    std::cin >> idEspecialidad;

    // Opcional: Validar existencia de médico y especialidad antes de guardar
    int posMedico = archivoMedico.Buscar(idMedico);
    int posEspecialidad = archivoEspecialidad.buscarPorId(idEspecialidad);
    if (posMedico == -1) {
        std::cout << "El medico no existe.\n";
        return;
    }
    if (posEspecialidad == -1) {
        std::cout << "La especialidad no existe.\n";
        return;
    }

    MedicoEspecialidad reg(nuevoId, idEspecialidad, idMedico);

    if (archivo.Guardar(reg)) {
        std::cout << "Relacion medico-especialidad registrada correctamente.\n";
    } else {
        std::cout << "Error al guardar la relacion.\n";
    }
}

void ManagerMedicoEspecialidad::eliminarMedicoEspecialidad() {
    ArchivoMedicoEspecialidad archivo("medico_especialidad.dat");
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

    FILE* pArchivo = fopen("medico_especialidad.dat", "wb");
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
    ArchivoMedicoEspecialidad archivo("medico_especialidad.dat");
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
    ArchivoMedicoEspecialidad archivo("medico_especialidad.dat");
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
    ArchivoMedicoEspecialidad archivo("medico_especialidad.dat");
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
