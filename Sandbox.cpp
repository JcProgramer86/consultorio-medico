#include <iostream>
#include "Medico.h"
#include "ArchivoMedico.h"
#include "Fecha.h"
#include "Paciente.h"
#include "ArchivoPaciente.h"
#include "Turnos.h"
#include "ArchivoTurno.h"
#include "ArchivoMedicoEspecialidad.h"
#include "ManagerAdministrativo.h"
#include "ArchivoPrestador.h"
#include "ArchivoEspecialidad.h"
#include <cstdio>

using namespace std;


void ejecutarSandboxMedico()
{
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

    if (archivo.Guardar(medicoTest))
    {
        std::cout << "Médico guardado correctamente." << std::endl;
    }
    else
    {
        std::cout << "Error al guardar el médico." << std::endl;
    }

    int cant = archivo.CantidadRegistros();

    for (int i = 0; i < cant; i++)
    {
        Medico medico = archivo.Leer(i);
        std::cout << medico.toCSV() << std::endl;
    }
}

void ejecutarSandboxPrestador()
{
    // 1) Crear un par de prestadores
    Prestador pr1(1, "", "Osde",true);
    pr1.generarCodigo("Osde");

    Prestador pr2(2, "", "Swiss Med",false);
    pr2.generarCodigo("Swiss Med");

    // 2) Instanciar el manejador de archivo
    ArchivoPrestador archivo("prestadores.dat");

    // 3) Guardar ambos registros
    if (archivo.Guardar(pr1) && archivo.Guardar(pr2))
    {
        std::cout << "Prestadores guardados correctamente." << std::endl;
    }
    else
    {
        std::cout << "Error al guardar los prestadores." << std::endl;
        return;
    }

    // 4) Leer y mostrar todos los registros
    int cantidad = archivo.CantidadRegistros();
    for (int i = 0; i < cantidad; ++i)
    {
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


void ejecutarSandboxPaciente()
{
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

    if (archivo.Guardar(paciente1) && archivo.Guardar(paciente2))
    {
        std::cout << "Pacientes guardados correctamente." << std::endl;
    }
    else
    {
        std::cout << "Error al guardar los pacientes." << std::endl;
    }

    int cantidad = archivo.CantidadRegistros();

    for (int i = 0; i < cantidad; i++)
    {
        Paciente paciente = archivo.Leer(i);
        std::cout << paciente.toCSV() << std::endl;
    }
}


void ejecutarBuscarPacientePorNombre(const std::string& nombreBuscado)
{
    ArchivoPaciente archivo("paciente.dat");
    int cantidad = archivo.CantidadRegistros();
    bool encontrado = false;

    for (int i = 0; i < cantidad; ++i)
    {
        Paciente paciente = archivo.Leer(i);
        if (paciente.get_nombre() == nombreBuscado)
        {
            std::cout << "Paciente encontrado:\n";
            std::cout << paciente.toCSV() << std::endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado)
    {
        std::cout << "Paciente con nombre '" << nombreBuscado << "' no encontrado." << std::endl;
    }
}


// prueba de creacion y muestra medico especialidad.

void ejecutarSandboxMedicoEspecialidad()
{
    MedicoEspecialidad me1(1, 101, 201);
    MedicoEspecialidad me2(2, 102, 202);

    ArchivoMedicoEspecialidad archivo("medicoespecialidades.dat");


    if (archivo.Guardar(me1) && archivo.Guardar(me2))
    {
        std::cout << "MedicoEspecialidad guardados correctamente." << std::endl;
    }
    else
    {
        std::cout << "Error al guardar MedicoEspecialidad." << std::endl;
        return;
    }


    int cantidad = archivo.CantidadRegistros();
    for (int i = 0; i < cantidad; ++i)
    {
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

void ejecutarSandboxTurno()
{
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

    if (archivo.Guardar(turnoTest))
    {
        std::cout << "Turno guardado correctamente." << std::endl;
    }
    else
    {
        std::cout << "Error al guardar el turno." << std::endl;
    }

    std::cout << "\nListado de turnos registrados:" << std::endl;
    archivo.ListarTurnos();
}


void imprimirTurno(const Turno& t)
{
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


void ejecutarBuscarTurnoPorId(int idBuscado)
{
    ArchivoTurno archivo("turnos.dat");
    int posicion = archivo.Buscar(idBuscado);

    if (posicion == -1)
    {
        std::cout << "Turno con ID " << idBuscado << " no encontrado." << std::endl;
        return;
    }

    Turno turnoEncontrado;

    if (turnoEncontrado.getId() != -1)   // Suponiendo que si no existe devuelve Turno con id=0
    {
        imprimirTurno(turnoEncontrado);
    }
    else
    {
        std::cout << "Error al leer el turno desde el archivo." << std::endl;
    }
}

//facturacion mensual

void ejecutarSandboxFacturacionMensual()
{
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

// Función auxiliar para crear datos de prueba en medicoespecialidad.dat
void crearDatosPruebaMedicoEspecialidad()
{
    ArchivoMedicoEspecialidad archivoMedicoEspecialidad("medicoespecialidad.dat");

    MedicoEspecialidad me1;
    me1.setId(201);
    me1.setIdMedico(1001);
    me1.setIdEspecialidad(201);

    MedicoEspecialidad me2;
    me2.setId(202);
    me2.setIdMedico(1002);
    me2.setIdEspecialidad(202);

    archivoMedicoEspecialidad.Guardar(me1);
    archivoMedicoEspecialidad.Guardar(me2);
}

void ejecutarSandboxListarPacientesAtendidosPorEspecialidadYMes()
{
    // Borramos archivos para datos limpios
    remove("paciente.dat");
    remove("turnos.dat");
    remove("medicoespecialidad.dat");

    // Crear pacientes de prueba
    Paciente p1, p2, p3;

    p1.set_id(10);
    p1.set_nombre("Luis");
    p1.set_apellido("Perez");
    p1.set_enabled(true);

    p2.set_id(11);
    p2.set_nombre("Ana");
    p2.set_apellido("Gomez");
    p2.set_enabled(true);

    p3.set_id(12);
    p3.set_nombre("Carlos");
    p3.set_apellido("Lopez");
    p3.set_enabled(true);

    ArchivoPaciente archiPac("paciente.dat");
    archiPac.Guardar(p1);
    archiPac.Guardar(p2);
    archiPac.Guardar(p3);

    // Crear datos médico-especialidad
    crearDatosPruebaMedicoEspecialidad();

    // Crear turnos de prueba
    Turno t1, t2, t3;

    t1.setId(2001);
    t1.setIdPaciente(10);
    t1.setIdMedicoEspecialidad(201);
    t1.setFechaAtencion(Fecha(5, 6, 2025));
    t1.setHoraAtencion(Hora(9, 0));
    t1.setCancelado(false);
    t1.setAsistio(true);

    t2.setId(2002);
    t2.setIdPaciente(11);
    t2.setIdMedicoEspecialidad(201);
    t2.setFechaAtencion(Fecha(15, 6, 2025));
    t2.setHoraAtencion(Hora(10, 0));
    t2.setCancelado(false);
    t2.setAsistio(true);

    t3.setId(2003);
    t3.setIdPaciente(12);
    t3.setIdMedicoEspecialidad(202);
    t3.setFechaAtencion(Fecha(20, 7, 2025));
    t3.setHoraAtencion(Hora(11, 0));
    t3.setCancelado(false);
    t3.setAsistio(true);

    ArchivoTurno archiTurno("turnos.dat");
    archiTurno.Guardar(t1);
    archiTurno.Guardar(t2);
    archiTurno.Guardar(t3);

    std::cout << "\n>>> Datos de prueba generados correctamente.\n\n";

    ManagerAdministrativo manager;
    manager.listarPacientesAtendidosPorEspecialidadYMes();

    system("pause");
}
//sandoboxes para medico submenues

void ejecutarSandboxOcupacionPorDiaDeMedico()
{
    // Borro archivos para datos limpios
    remove("medico.dat");
    remove("turnos.dat");

    // Creo un médico de prueba
    Medico m1;
    m1.set_id(1001);
    m1.set_dni("20976055");  // DNI de ejemplo
    m1.set_nombre("Valeria");
    m1.set_apellido("Morandi");
    m1.set_enabled(true);

    ArchivoMedico archivoMedico("medico.dat");
    archivoMedico.Guardar(m1);

    // Creo turnos de prueba para ese médico
    ArchivoTurno archivoTurno("turnos.dat");

    Turno t1;
    t1.setId(1);
    t1.setIdMedicoEspecialidad(1001);
    t1.setFechaAtencion(Fecha(20, 6, 2025));
    t1.setHoraAtencion(Hora(9, 0));
    t1.setAsistio(true);
    t1.setCancelado(false);
    archivoTurno.Guardar(t1);

    Turno t2;
    t2.setId(2);
    t2.setIdMedicoEspecialidad(1001);
    t2.setFechaAtencion(Fecha(20, 6, 2025));
    t2.setHoraAtencion(Hora(10, 0));
    t2.setAsistio(true);
    t2.setCancelado(false);
    archivoTurno.Guardar(t2);

    Turno t3;
    t3.setId(3);
    t3.setIdMedicoEspecialidad(1001);
    t3.setFechaAtencion(Fecha(21, 6, 2025));
    t3.setHoraAtencion(Hora(9, 0));
    t3.setAsistio(true);
    t3.setCancelado(false);
    archivoTurno.Guardar(t3);

    // Creo instancia del manager y ejecuto método
    ManagerAdministrativo manager;
    manager.ocupacionPorDiaDeMedico();

    system("pause");
}

void ejecutarSandboxOcupacionPorMesDeMedico()
{
    // Borro archivos para datos limpios
    remove("medico.dat");
    remove("turnos.dat");

    // Creo un médico de prueba
    Medico m1;
    m1.set_id(1001);
    m1.set_dni("20976055");  // DNI de ejemplo
    m1.set_nombre("Valeria");
    m1.set_apellido("Morandi");
    m1.set_enabled(true);

    ArchivoMedico archivoMedico("medico.dat");
    archivoMedico.Guardar(m1);

    // Creo turnos de prueba para ese médico
    ArchivoTurno archivoTurno("turnos.dat");

    Turno t1;
    t1.setId(1);
    t1.setIdMedicoEspecialidad(1001);
    t1.setFechaAtencion(Fecha(20, 6, 2025));
    t1.setHoraAtencion(Hora(9, 0));
    t1.setAsistio(true);
    t1.setCancelado(false);
    archivoTurno.Guardar(t1);

    Turno t2;
    t2.setId(2);
    t2.setIdMedicoEspecialidad(1001);
    t2.setFechaAtencion(Fecha(21, 6, 2025));
    t2.setHoraAtencion(Hora(10, 0));
    t2.setAsistio(true);
    t2.setCancelado(false);
    archivoTurno.Guardar(t2);

    Turno t3;
    t3.setId(3);
    t3.setIdMedicoEspecialidad(1001);
    t3.setFechaAtencion(Fecha(15, 7, 2025));
    t3.setHoraAtencion(Hora(11, 0));
    t3.setAsistio(true);
    t3.setCancelado(false);
    archivoTurno.Guardar(t3);

    // Creo instancia del manager y ejecuto método
    ManagerAdministrativo manager;
    manager.ocupacionPorMesDeMedico();

    system("pause");
}
void ejecutarSandboxOcupacionPorMesEspecialidad() {
    // Borrar archivos para datos limpios
    remove("especialidad.dat");
    remove("turnos.dat");
    remove("medicoespecialidad.dat");

    // Crear especialidades de prueba
    Especialidad e1(1, "Cardiologia");
    Especialidad e2(2, "Neumonologia");
    Especialidad e3(3, "Dermatologia");

    ArchivoEspecialidad archivoEsp("especialidad.dat");
    archivoEsp.guardar(e1);
    archivoEsp.guardar(e2);
    archivoEsp.guardar(e3);

    // Crear médicos y médico-especialidad
    Medico m1; m1.set_id(100); m1.set_nombre("Juan"); m1.set_apellido("Perez"); m1.set_enabled(true);
    Medico m2; m2.set_id(101); m2.set_nombre("Ana"); m2.set_apellido("Lopez"); m2.set_enabled(true);

    ArchivoMedico archivoMed("medico.dat");
    archivoMed.Guardar(m1);
    archivoMed.Guardar(m2);

    MedicoEspecialidad me1(200, 1, 100); // Cardiologia - Juan
    MedicoEspecialidad me2(201, 2, 101); // Neumonologia - Ana

    ArchivoMedicoEspecialidad archivoMedEsp("medicoespecialidad.dat");
    archivoMedEsp.Guardar(me1);
    archivoMedEsp.Guardar(me2);

    // Crear turnos para diferentes días y meses
    Turno t1; t1.setId(1); t1.setIdPaciente(1); t1.setIdMedicoEspecialidad(200);
    t1.setFechaAtencion(Fecha(5, 6, 2025)); t1.setHoraAtencion(Hora(9, 0)); t1.setCancelado(false); t1.setAsistio(true);

    Turno t2; t2.setId(2); t2.setIdPaciente(2); t2.setIdMedicoEspecialidad(201);
    t2.setFechaAtencion(Fecha(10, 6, 2025)); t2.setHoraAtencion(Hora(10, 0)); t2.setCancelado(false); t2.setAsistio(true);

    Turno t3; t3.setId(3); t3.setIdPaciente(3); t3.setIdMedicoEspecialidad(200);
    t3.setFechaAtencion(Fecha(15, 7, 2025)); t3.setHoraAtencion(Hora(11, 0)); t3.setCancelado(false); t3.setAsistio(true);

    ArchivoTurno archivoTurno("turnos.dat");
    archivoTurno.Guardar(t1);
    archivoTurno.Guardar(t2);
    archivoTurno.Guardar(t3);

    // Ejecutar método del manager
    ManagerAdministrativo manager;
    manager.ocupacionPorMesEspecialidad();

    system("pause");
}
void ejecutarSandboxOcupacionTotalPorMes()
{
    // Inicializar archivos
    ArchivoTurno archivoTurno("turnos.dat");
    ArchivoMedico archivoMedico("medico.dat");

    // Simulamos 2 médicos
    Medico m1, m2;
    m1.set_id(1);
    m1.set_dni("20111222");
    m1.set_nombre("Ana");
    m1.set_apellido("Suarez");

    m2.set_id(2);
    m2.set_dni("30999888");
    m2.set_nombre("Luis");
    m2.set_apellido("Gomez");

    archivoMedico.Guardar(m1);
    archivoMedico.Guardar(m2);

    // Simulamos 5 turnos (4 en junio 2025, 1 en mayo)
    Turno t1, t2, t3, t4, t5;

    t1.setIdMedicoEspecialidad(1);
    t1.setIdPaciente(101);
    t1.setFechaAtencion(Fecha(10, 6, 2025));
    t1.setHoraAtencion(Hora(9, 0));
    t1.setImporteConsulta(3000.0f);
    t1.setCancelado(false);
    t1.setAsistio(true);

    t2 = t1;
    t2.setFechaAtencion(Fecha(12, 6, 2025));

    t3 = t1;
    t3.setIdMedicoEspecialidad(2);
    t3.setFechaAtencion(Fecha(15, 6, 2025));

    t4 = t1;
    t4.setIdMedicoEspecialidad(2);
    t4.setFechaAtencion(Fecha(20, 6, 2025));

    t5 = t1;
    t5.setFechaAtencion(Fecha(30, 5, 2025)); // No debe contarse

    archivoTurno.Guardar(t1);
    archivoTurno.Guardar(t2);
    archivoTurno.Guardar(t3);
    archivoTurno.Guardar(t4);
    archivoTurno.Guardar(t5);

    // Ejecutar prueba
    ManagerAdministrativo manager;
    manager.ocupacionTotalPorMes();
}
