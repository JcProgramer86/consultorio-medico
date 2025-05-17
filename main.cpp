#include <iostream>
#include "Persona.h"
#include <locale>
#include "ArchivoMedico.h"
#include "Medico.h"

using namespace std;

int main() {

    Fecha fechaNac(15, 6, 1985);
    Fecha fechaIni(1, 3, 2010);
    Medico medico;

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

    // Crear objeto Archivo
    ArchivoMedico archivo("medicos.dat");

    // Guardar
    if (archivo.Guardar(medicoTest)) {
        std::cout << "Medico guardado correctamente." << std::endl;
    } else {
        std::cout << "Error al guardar el médico." << std::endl;
    }

    int cant = archivo.CantidadRegistros();

    for(int i = 0; i< cant;i++){
        medico = archivo.Leer(i);
        cout<<medico.toCSV()<<endl;
    }



    return 0;
}
