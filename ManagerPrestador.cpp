#include "ManagerPrestador.h"
#include "ArchivoPrestador.h"
#include "Prestador.h"
#include "Persona.h"
#include "Menu.h"
#include <iostream>
#include <iomanip>

extern Menu menu;

void ManagerPrestador::cargarNuevoPrestador() {
    system("cls");
    menu.menuHeader();

    ArchivoPrestador archivoPrestador("prestadores.dat");
    int id = archivoPrestador.CantidadRegistros() > 0 ?
             archivoPrestador.Leer(archivoPrestador.CantidadRegistros()-1).getId() + 1 : 1;

    std::string nombre;
    std::cout << "\n========================================" << std::endl;
    std::cout << "          ALTA DE NUEVO PRESTADOR       " << std::endl;
    std::cout << "========================================" << std::endl;

    std::cout << "Ingrese el nombre del prestador: ";
    std::cin.ignore();
    std::getline(std::cin, nombre);

    while (!Persona::validarTexto(nombre)) {
        std::cout << "[!] El nombre solo debe contener letras. Intente nuevamente: ";
        std::getline(std::cin, nombre);
    }

    // Generar código (lo podés personalizar según tu sistema)
    Prestador tempPrestador;
    tempPrestador.generarCodigo(nombre);
    std::string cod = tempPrestador.getCodPrestador();

    Prestador prestador(id, cod, nombre, true);

    if (archivoPrestador.Guardar(prestador)) {
        std::cout << "[OK] Prestador guardado correctamente." << std::endl;
    } else {
        std::cout << "[ERROR] No se pudo guardar el prestador." << std::endl;
    }
    std::cout << "Presione Enter para continuar...";
    std::cin.get();
}

void ManagerPrestador::listarPrestadores() {
    system("cls");
    menu.menuHeader();

    ArchivoPrestador archivoPrestador("prestadores.dat");
    int cantidad = archivoPrestador.CantidadRegistros();

    std::cout << "\n========================================" << std::endl;
    std::cout << "          LISTADO DE PRESTADORES        " << std::endl;
    std::cout << "========================================" << std::endl;

    if (cantidad == 0) {
        std::cout << "No hay prestadores cargados." << std::endl;
    } else {
        std::cout << std::left << std::setw(5) << "ID"
                  << std::setw(15) << "Código"
                  << std::setw(30) << "Nombre"
                  << std::setw(10) << "Estado" << std::endl;
        std::cout << std::string(60, '-') << std::endl;

        for (int i = 0; i < cantidad; ++i) {
            Prestador p = archivoPrestador.Leer(i);
            std::cout << std::left << std::setw(5) << p.getId()
                      << std::setw(15) << p.getCodPrestador()
                      << std::setw(30) << p.getNombrePrestador()
                      << std::setw(10) << (p.isEnabled() ? "Activo" : "Baja") << std::endl;
        }
        std::cout << std::string(60, '-') << std::endl;
    }
    std::cout << "Presione Enter para continuar...";
    std::cin.ignore();
    std::cin.get();
}

void ManagerPrestador::modificarPrestadorPorId() {
    system("cls");
    menu.menuHeader();

    ArchivoPrestador archivoPrestador("prestadores.dat");
    int cantidad = archivoPrestador.CantidadRegistros();

    if (cantidad == 0) {
        std::cout << "\nNo hay prestadores cargados para modificar." << std::endl;
        std::cout << "Presione Enter para continuar...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    listarPrestadores();

    int id, pos = -1;
    std::cout << "Ingrese el ID del prestador a modificar: ";
    std::cin >> id;

    pos = archivoPrestador.Buscar(id);
    if (pos == -1) {
        std::cout << "[!] Prestador no encontrado." << std::endl;
        std::cout << "Presione Enter para continuar...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    Prestador p = archivoPrestador.Leer(pos);

    std::string nombreNuevo;
    std::cout << "Ingrese el nuevo nombre del prestador (actual: " << p.getNombrePrestador() << "): ";
    std::cin.ignore();
    std::getline(std::cin, nombreNuevo);

    while (!Persona::validarTexto(nombreNuevo)) {
        std::cout << "[!] El nombre solo debe contener letras. Intente nuevamente: ";
        std::getline(std::cin, nombreNuevo);
    }

    p.setNombrePrestador(nombreNuevo);
    p.generarCodigo(nombreNuevo);

    if (archivoPrestador.Guardar(p, pos)) {
        std::cout << "[OK] Prestador modificado correctamente." << std::endl;
    } else {
        std::cout << "[ERROR] No se pudo modificar el prestador." << std::endl;
    }
    std::cout << "Presione Enter para continuar...";
    std::cin.get();
}

void ManagerPrestador::eliminarPrestadorPorId() {
    system("cls");
    menu.menuHeader();

    ArchivoPrestador archivoPrestador("prestadores.dat");
    int cantidad = archivoPrestador.CantidadRegistros();

    if (cantidad == 0) {
        std::cout << "\nNo hay prestadores cargados para eliminar." << std::endl;
        std::cout << "Presione Enter para continuar...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    listarPrestadores();

    int id, pos = -1;
    std::cout << "Ingrese el ID del prestador a dar de baja: ";
    std::cin >> id;

    pos = archivoPrestador.Buscar(id);
    if (pos == -1) {
        std::cout << "[!] Prestador no encontrado." << std::endl;
        std::cout << "Presione Enter para continuar...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    Prestador p = archivoPrestador.Leer(pos);

    if (!p.isEnabled()) {
        std::cout << "[!] El prestador ya está dado de baja." << std::endl;
    } else {
        p.setEnabled(false);
        if (archivoPrestador.Guardar(p, pos)) {
            std::cout << "[OK] Prestador dado de baja correctamente." << std::endl;
        } else {
            std::cout << "[ERROR] No se pudo dar de baja el prestador." << std::endl;
        }
    }
    std::cout << "Presione Enter para continuar...";
    std::cin.ignore();
    std::cin.get();
}
