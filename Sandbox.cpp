#include <iostream>
#include "Medico.h"
#include "ArchivoMedico.h"
#include "Fecha.h"
#include "Paciente.h"
#include "ArchivoPaciente.h"


void ejecutarSandboxMedico() {
    Fecha fechaNac(15, 6, 1985);
    Fecha fechaIni(1, 3, 2010);

    Medico medicoTest(
        1,
        "12345678",
        "Juan",
        "Perez",
        "1123456789",
        "juan@email.com",
        fechaNac,
        3,
        fechaIni
    );

    ArchivoMedico archivo("medicos.dat");

    if (archivo.Guardar(medicoTest)) {
        std::cout << "Médico guardado correctamente." << std::endl;
    } else {
        std::cout << "Error al guardar el médico." << std::endl;
    }

    int cant = archivo.CantidadRegistros();

    for (int i = 0; i < cant; i++) {
        Medico medico = archivo.Leer(i);
        std::cout << medico.toCSV() << std::endl;
    }
}


void ejecutarSandboxPaciente() {
    Fecha fechaNac1(12, 5, 1990);
    Fecha fechaNac2(8, 11, 1987);

    Paciente paciente1(
        1,
        "32145678",
        "Ana",
        "Gomez",
        "1134567890",
        "ana@email.com",
        10,
        fechaNac1
    );

    Paciente paciente2(
        2,
        "28945678",
        "Luis",
        "Martinez",
        "1149876543",
        "luis@email.com",
        12,
        fechaNac2
    );

    ArchivoPaciente archivo("pacientes.dat");

    if (archivo.Guardar(paciente1) && archivo.Guardar(paciente2)) {
        std::cout << "Pacientes guardados correctamente." << std::endl;
    } else {
        std::cout << "Error al guardar los pacientes." << std::endl;
    }

    int cantidad = archivo.CantidadRegistros();

    for (int i = 0; i < cantidad; i++) {
        Paciente paciente = archivo.Leer(i);
        std::cout << paciente.toCSV() << std::endl;
    }
}


void ejecutarBuscarPacientePorNombre(const std::string& nombreBuscado) {
    ArchivoPaciente archivo("pacientes.dat");
    int cantidad = archivo.CantidadRegistros();
    bool encontrado = false;

    for (int i = 0; i < cantidad; ++i) {
        Paciente paciente = archivo.Leer(i);
        if (paciente.get_nombre() == nombreBuscado) {
            std::cout << "Paciente encontrado:\n";
            std::cout << paciente.toCSV() << std::endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        std::cout << "Paciente con nombre '" << nombreBuscado << "' no encontrado." << std::endl;
    }
}

