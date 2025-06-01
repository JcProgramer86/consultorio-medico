#include <iostream>
#include "Medico.h"
#include "ArchivoMedico.h"
#include "Fecha.h"
#include "Paciente.h"
#include "ArchivoPaciente.h"
#include "Turnos.h"
#include "ArchivoTurno.h"
#include "ArchivoMedicoEspecialidad.h"
#include "ArchivoPrestador.h"


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
    fechaIni,
    "MAT12345"    // <-- Aquí va la matrícula, por ejemplo
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

void ejecutarSandboxPrestador() {
    // 1) Crear un par de prestadores
    Prestador pr1(1, "", "Osde",true);
    pr1.generarCodigo("Osde");

    Prestador pr2(2, "", "Swiss Med",false);
    pr2.generarCodigo("Swiss Med");

    // 2) Instanciar el manejador de archivo
    ArchivoPrestador archivo("prestadores.dat");

    // 3) Guardar ambos registros
    if (archivo.Guardar(pr1) && archivo.Guardar(pr2)) {
        std::cout << "Prestadores guardados correctamente." << std::endl;
    } else {
        std::cout << "Error al guardar los prestadores." << std::endl;
        return;
    }

    // 4) Leer y mostrar todos los registros
    int cantidad = archivo.CantidadRegistros();
    for (int i = 0; i < cantidad; ++i) {
        Prestador p = archivo.Leer(i);
        std::cout
            << "Registro " << i << ": "
            << "ID="     << p.getId()
            << ", Código="  << p.getCodPrestador()
            << ", Nombre="  << p.getNombrePrestador()
            << ", Habilitado=" << (p.isEnabled() ? "sí" : "no")
            << std::endl;
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


// prueba de creacion y muestra medico especialidad.

void ejecutarSandboxMedicoEspecialidad(){
    MedicoEspecialidad me1(1, 101, 201);
    MedicoEspecialidad me2(2, 102, 202);

    ArchivoMedicoEspecialidad archivo("medicoespecialidades.dat");


    if (archivo.Guardar(me1) && archivo.Guardar(me2)) {
        std::cout << "MedicoEspecialidad guardados correctamente." << std::endl;
    } else {
        std::cout << "Error al guardar MedicoEspecialidad." << std::endl;
        return;
    }


    int cantidad = archivo.CantidadRegistros();
    for (int i = 0; i < cantidad; ++i) {
        MedicoEspecialidad m = archivo.Leer(i);
        std::cout
            << "Registro " << i << ": "
            << "ID=" << m.getId()
            << ", IdEspecialidad=" << m.getIdEspecialidad()
            << ", IdMedico=" << m.getIdMedico()
            << std::endl;
    }
}

//turnos

void ejecutarSandboxTurno() {
    // Crear fecha y hora de ejemplo
    Fecha fechaTurno(25, 5, 2025);
    Hora horaTurno(10, 30);

    int pacientes[10];
    int medicos[10];
    for (int i = 0; i < 10; i++) {
        pacientes[i] = i + 1;
        medicos[i] = 100 + i;
    }

    Turno turnoTest;
    turnoTest.setIdTurno(1001);
    turnoTest.setIdPaciente(pacientes);
    turnoTest.setIdMedico(medicos);
    turnoTest.setFechaTurno(fechaTurno);
    turnoTest.setHoraTurno(horaTurno);
    turnoTest.setImporteConsulta(7500.0f);

    ArchivoTurno archivo("turnos.dat");

    if (archivo.GuardarTurno(turnoTest)) {
        std::cout << "Turno guardado correctamente." << std::endl;
    } else {
        std::cout << "Error al guardar el turno." << std::endl;
    }

    std::cout << "\nListado de turnos registrados:" << std::endl;
    archivo.ListarTurnos();
}

void ejecutarBuscarTurnoPorId(int idBuscado) {
    ArchivoTurno archivo("turnos.dat");
    int posicion = archivo.BuscarTurnoPorId(idBuscado);

    if (posicion == -1) {
        std::cout << "Turno con ID " << idBuscado << " no encontrado." << std::endl;
        return;
    }

    Turno turnoEncontrado;
    if (archivo.LeerTurno(turnoEncontrado, posicion)) {
        std::cout << "Turno encontrado:" << std::endl;
        std::cout << "ID Turno: " << turnoEncontrado.getIdTurno() << std::endl;

        std::cout << "Pacientes IDs: ";
        const int* pacientes = turnoEncontrado.getIdPaciente();
        for (int i = 0; i < 10; ++i) {
            std::cout << pacientes[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "Médicos IDs: ";
        const int* medicos = turnoEncontrado.getIdMedico();
        for (int i = 0; i < 10; ++i) {
            std::cout << medicos[i] << " ";
        }
        std::cout << std::endl;

        Fecha fecha = turnoEncontrado.getFechaTurno();
        std::cout << "Fecha del turno: " << fecha.getDia() << "/" << fecha.getMes() << "/" << fecha.getAnio() << std::endl;

        Hora hora = turnoEncontrado.getHoraTurno();
        std::cout << "Hora del turno: " << hora.getHora() << ":" << hora.getMinuto()  << std::endl;

        std::cout << "Importe consulta: $" << turnoEncontrado.getImporteConsulta() << std::endl;
    } else {
        std::cout << "Error al leer el turno desde el archivo." << std::endl;
    }
}
