#include <iostream>
#include "Medico.h"
#include "ArchivoMedico.h"
#include "Fecha.h"
#include "Paciente.h"
#include "ArchivoPaciente.h"
#include "Turnos.h"
#include "ArchivoTurno.h"


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
    Paciente paciente1(
        101,
        "87654321",
        "Ana",
        "Gomez",
        "1198765432",
        "ana@email.com",
        1, // idPrestador
        fechaNac1
    );

    Fecha fechaNac2(22, 1, 1980);
    Paciente paciente2(
        102,
        "11223344",
        "Luis",
        "Fernandez",
        "1155443322",
        "luis@email.com",
        2, // idPrestador
        fechaNac2
    );

    ArchivoPaciente archivo("pacientes.dat");

    if (archivo.Guardar(paciente1)) {
        std::cout << "Paciente 1 guardado correctamente." << std::endl;
    } else {
        std::cout << "Error al guardar el paciente 1." << std::endl;
    }

    if (archivo.Guardar(paciente2)) {
        std::cout << "Paciente 2 guardado correctamente." << std::endl;
    } else {
        std::cout << "Error al guardar el paciente 2." << std::endl;
    }

    int cant = archivo.CantidadRegistros();
    std::cout << "Cantidad de pacientes: " << cant << std::endl;

    for (int i = 0; i < cant; i++) {
        Paciente paciente = archivo.Leer(i);
        std::cout << paciente.toCSV() << std::endl;
    }
}

void ejecutarBuscarPacientePorNombre(const std::string& nombreBuscado) {
    ArchivoPaciente archivo("pacientes.dat");
    int posicion = archivo.BuscarPorNombre(const_cast<std::string&>(nombreBuscado)); // Se necesita const_cast si el método no es const

    if (posicion != -1) {
        Paciente pacienteEncontrado = archivo.Leer(posicion);
        std::cout << "Paciente encontrado por nombre '" << nombreBuscado << "':" << std::endl;
        std::cout << pacienteEncontrado.toCSV() << std::endl;
    } else {
        std::cout << "Paciente con nombre '" << nombreBuscado << "' no encontrado." << std::endl;
    }
}

void ejecutarSandboxTurno() {
    ArchivoTurno archivo("turnos.dat");

    // Crear un turno de ejemplo
    int pacientes1[] = {201, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    int medicosEspecialidad1[] = {1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    Fecha fecha1(25, 5, 2024);
    Hora hora1(10, 0);
    Turno turno1(1, pacientes1, medicosEspecialidad1, fecha1, hora1, 1500.0f, false, false, "Consulta general");

    // Guardar el turno
    if (archivo.GuardarTurno(turno1)) {
        std::cout << "Turno guardado correctamente." << std::endl;
    } else {
        std::cout << "Error al guardar el turno." << std::endl;
    }

    // Listar todos los turnos
    archivo.ListarTurnos();
}

void ejecutarBuscarTurnoPorId(int idBuscado) {
    ArchivoTurno archivo("turnos.dat");
    int posicion = archivo.BuscarTurnoPorId(idBuscado);

    if (posicion == -1) {
        std::cout << "Turno con ID " << idBuscado << " no encontrado." << std::endl;
        return;
    }

    Turno turnoEncontrado = archivo.LeerTurno(posicion);
    std::cout << "Turno encontrado:" << std::endl;
    std::cout << "ID Turno: " << turnoEncontrado.getIdTurno() << std::endl;

    std::cout << "Pacientes IDs: ";
    const int* pacientes = turnoEncontrado.getIdPaciente();
    for (int i = 0; i < 10; ++i) {
        if (pacientes[i] != -1) {
            std::cout << pacientes[i] << " ";
        }
    }
    std::cout << std::endl;

    std::cout << "Médicos IDs: ";
    const int* medicos = turnoEncontrado.getIdMedicoEspecialidad();
    for (int i = 0; i < 10; ++i) {
        if (medicos[i] != -1) {
            std::cout << medicos[i] << " ";
        }
    }
    std::cout << std::endl;

    Fecha fecha = turnoEncontrado.getFechaAtencion();
    std::cout << "Fecha del turno: " << fecha.getDia() << "/" << fecha.getMes() << "/" << fecha.getAnio() << std::endl;
    Hora hora = turnoEncontrado.getHoraAtencion();
    std::cout << "Hora del turno: " << hora.getHoraAtencion() << ":" << hora.getMinutoAtencion() << std::endl;
    std::cout << "Importe: " << turnoEncontrado.getImporteConsulta() << std::endl;
    std::cout << "Cancelado: " << (turnoEncontrado.getCancelado() ? "Sí" : "No") << std::endl;
    std::cout << "Sobreturno: " << (turnoEncontrado.getSobreturno() ? "Sí" : "No") << std::endl;
    Hora duracion = turnoEncontrado.getDuracionTurno();
    std::cout << "Duración: " << duracion.getHoraAtencion() << "h " << duracion.getMinutoAtencion() << "min" << std::endl;
    std::cout << "Observaciones: " << turnoEncontrado.getObservaciones() << std::endl;
}


