#include <iostream>
#include "Medico.h"
#include "ArchivoMedico.h"
#include "Fecha.h"

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
