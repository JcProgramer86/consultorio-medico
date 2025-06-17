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
#include "ManagerAdministrativo.h"


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
    "MAT12345",    // <-- Aquí va la matrícula, por ejemplo
    true
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

    // Carga simple de datos demo
    int idPaciente = 1;
    int idMedicoEspecialidad = 100;

    Turno turnoTest;
    turnoTest.setId(1001);
    turnoTest.setIdPaciente(idPaciente);
    turnoTest.setIdMedicoEspecialidad(idMedicoEspecialidad);
    turnoTest.setFechaAtencion(fechaTurno);
    turnoTest.setHoraAtencion(horaTurno);
    turnoTest.setImporteConsulta(7500.0f);
    turnoTest.setCancelado(false);
    turnoTest.setSobreturno(false);
    turnoTest.setDuracionTurno(Hora(0, 20));
    turnoTest.setObservaciones("Prueba sandbox");

    ArchivoTurno archivo("turnos.dat");

    if (archivo.Guardar(turnoTest)) {
        std::cout << "Turno guardado correctamente." << std::endl;
    } else {
        std::cout << "Error al guardar el turno." << std::endl;
    }

    std::cout << "\nListado de turnos registrados:" << std::endl;
    archivo.ListarTurnos();
}


void imprimirTurno(const Turno& t) {
    std::cout << "ID Turno: " << t.getId() << std::endl;
    std::cout << "ID Paciente: " << t.getIdPaciente() << std::endl;
    std::cout << "ID MedicoEspecialidad: " << t.getIdMedicoEspecialidad() << std::endl;

    Fecha fecha = t.getFechaAtencion();
    std::cout << "Fecha del turno: " << fecha.getDia() << "/" << fecha.getMes() << "/" << fecha.getAnio() << std::endl;

    Hora hora = t.getHoraAtencion();
    std::cout << "Hora del turno: " << hora.getHora() << ":" << hora.getMinuto() << std::endl;

    std::cout << "Importe consulta: $" << t.getImporteConsulta() << std::endl;
    std::cout << "Observaciones: " << t.getObservaciones() << std::endl;
}


void ejecutarBuscarTurnoPorId(int idBuscado) {
    ArchivoTurno archivo("turnos.dat");
    int posicion = archivo.Buscar(idBuscado);

    if (posicion == -1) {
        std::cout << "Turno con ID " << idBuscado << " no encontrado." << std::endl;
        return;
    }

    Turno turnoEncontrado;

    if (turnoEncontrado.getId() != -1) { // Suponiendo que si no existe devuelve Turno con id=0
        imprimirTurno(turnoEncontrado);
    } else {
        std::cout << "Error al leer el turno desde el archivo." << std::endl;
    }
}

//facturacion mensual

void ejecutarSandboxFacturacionMensual() {
    // Generar algunos turnos de prueba
    ArchivoTurno archivo("turnos.dat");

    Turno t1;
    t1.setId(2001);
    t1.setIdPaciente(10);
    t1.setIdMedicoEspecialidad(101);
    t1.setFechaAtencion(Fecha(10, 6, 2025));  // Junio 2025
    t1.setHoraAtencion(Hora(9, 0));
    t1.setImporteConsulta(5000.0f);
    t1.setCancelado(false);
    t1.setSobreturno(false);
    t1.setDuracionTurno(Hora(0, 15));
    t1.setObservaciones("Consulta general");

    Turno t2;
    t2.setId(2002);
    t2.setIdPaciente(11);
    t2.setIdMedicoEspecialidad(102);
    t2.setFechaAtencion(Fecha(20, 6, 2025));  // Junio 2025
    t2.setHoraAtencion(Hora(10, 30));
    t2.setImporteConsulta(7000.0f);
    t2.setCancelado(false);
    t2.setSobreturno(false);
    t2.setDuracionTurno(Hora(0, 15));
    t2.setObservaciones("Especialidad");

    Turno t3;
    t3.setId(2003);
    t3.setIdPaciente(12);
    t3.setIdMedicoEspecialidad(103);
    t3.setFechaAtencion(Fecha(5, 7, 2025));  // Julio 2025
    t3.setHoraAtencion(Hora(11, 0));
    t3.setImporteConsulta(6000.0f);
    t3.setCancelado(false);
    t3.setSobreturno(false);
    t3.setDuracionTurno(Hora(0, 15));
    t3.setObservaciones("Chequeo");

    archivo.Guardar(t1);
    archivo.Guardar(t2);
    archivo.Guardar(t3);

    std::cout << "Turnos de prueba generados.\n";

    // Llamar al cálculo de facturación
    ManagerAdministrativo manager;
    float facturacion = manager.obtenerFacturacionDelMes();

    std::cout << "Facturación total de Junio 2025: $" << facturacion << std::endl;

    system("pause");
}
