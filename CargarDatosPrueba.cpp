
#include <iostream>
#include <cstdio>   // para remove()
#include <string>

#include "ArchivoMedico.h"
#include "ArchivoPaciente.h"
#include "ArchivoEspecialidad.h"
#include "ArchivoMedicoEspecialidad.h"
#include "ArchivoTurno.h"

#include "Medico.h"
#include "Paciente.h"
#include "Especialidad.h"
#include "MedicoEspecialidad.h"
#include "Turnos.h"
#include "Fecha.h"

using namespace std;

// Función para borrar archivos antes de cargar datos
void limpiarArchivos() {
    cout << "Limpiando archivos .dat..." << endl;
    remove("medico.dat");
    remove("paciente.dat");
    remove("especialidad.dat");
    remove("medicoespecialidad.dat");
    remove("turnos.dat");
    cout << "Archivos limpiados." << endl << endl;
}

void cargarEspecialidades() {
    ArchivoEspecialidad archivoEsp("especialidad.dat");
    cout << "Cargando especialidades..." << endl;

    archivoEsp.guardar(Especialidad(1, "Cardiologia"));
    archivoEsp.guardar(Especialidad(2, "Clinica Medica"));
    archivoEsp.guardar(Especialidad(3, "Psicologia"));

    cout << "3 especialidades cargadas." << endl << endl;
}

void cargarMedicos() {
    ArchivoMedico archivoMed("medico.dat");
    cout << "Cargando medicos..." << endl;

 archivoMed.Guardar(Medico(1, "12345678", "Juan", "Perez", "1122334455", "juan.perez@mail.com", Fecha(15,3,1980), 1, Fecha(1,1,2010), "MAT12345", true));
archivoMed.Guardar(Medico(2, "87654321", "Ana", "Gomez", "1199887766", "ana.gomez@mail.com", Fecha(22,7,1975), 2, Fecha(15,6,2005), "MAT67890", true));
archivoMed.Guardar(Medico(3, "23456789", "Luis", "Martinez", "1144778899", "luis.martinez@mail.com", Fecha(9,11,1985), 3, Fecha(20,3,2012), "MAT23456", true));
archivoMed.Guardar(Medico(4, "98765432", "Maria", "Lopez", "1177558899", "maria.lopez@mail.com", Fecha(3,5,1978), 1, Fecha(10,7,2008), "MAT34567", true));
archivoMed.Guardar(Medico(5, "34567890", "Carlos", "Sanchez", "1166335588", "carlos.sanchez@mail.com", Fecha(29,2,1984), 2, Fecha(5,9,2015), "MAT45678", true));


    cout << "5 medicos cargados." << endl << endl;
}

void cargarPacientes() {
    ArchivoPaciente archivoPac("paciente.dat");
    cout << "Cargando pacientes..." << endl;

    archivoPac.Guardar(Paciente(1, "41234567", "Sofia", "Fernandez", "1144556677", "sofia.fernandez@mail.com", 1, Fecha(2, 4, 1990), true));
    archivoPac.Guardar(Paciente(2, "42345678", "Diego", "Ruiz", "1155443322", "diego.ruiz@mail.com", 1, Fecha(10, 8, 1988), true));
    archivoPac.Guardar(Paciente(3, "43456789", "Martina", "Gonzalez", "1166223344", "martina.gonzalez@mail.com", 1, Fecha(18, 12, 1992), true));
    archivoPac.Guardar(Paciente(4, "44567890", "Lucas", "Diaz", "1177332211", "lucas.diaz@mail.com", 1, Fecha(25, 1, 1987), true));
    archivoPac.Guardar(Paciente(5, "45678901", "Valentina", "Morales", "1188445566", "valentina.morales@mail.com", 1, Fecha(30, 6, 1995), true));
    archivoPac.Guardar(Paciente(6, "46789012", "Emilia", "Torres", "1199556677", "emilia.torres@mail.com", 1, Fecha(12, 9, 1989), true));
    archivoPac.Guardar(Paciente(7, "47890123", "Tomas", "Paz", "1166778899", "tomas.paz@mail.com", 1, Fecha(8, 10, 1991), true));
    archivoPac.Guardar(Paciente(8, "48901234", "Camila", "Silva", "1144992266", "camila.silva@mail.com", 1, Fecha(14, 2, 1993), true));
    archivoPac.Guardar(Paciente(9, "49012345", "Nicolas", "Mendez", "1133884477", "nicolas.mendez@mail.com", 1, Fecha(19, 5, 1990), true));
    archivoPac.Guardar(Paciente(10, "50123456", "Agustina", "Ramos", "1122556699", "agustina.ramos@mail.com", 1, Fecha(6, 11, 1994), true));

    cout << "10 pacientes cargados." << endl << endl;
}


void cargarMedicoEspecialidad() {
    ArchivoMedicoEspecialidad archivoMedEsp("medicoespecialidad.dat");
    cout << "Cargando medico-especialidad..." << endl;

    archivoMedEsp.Guardar(MedicoEspecialidad(1, 1, 1));
    archivoMedEsp.Guardar(MedicoEspecialidad(2, 2, 2));
    archivoMedEsp.Guardar(MedicoEspecialidad(3, 3, 3));
    archivoMedEsp.Guardar(MedicoEspecialidad(4, 1, 4));
    archivoMedEsp.Guardar(MedicoEspecialidad(5, 2, 5));

    cout << "5 medico-especialidad cargados." << endl << endl;
}

void cargarTurnos() {
    ArchivoTurno archivoTurno("turnos.dat");
    cout << "Cargando turnos..." << endl;

    for (int i = 1; i <= 20; ++i) {
        Turno t;
        t.setId(i);
        t.setIdPaciente((i - 1) % 10 + 1);
        t.setIdMedicoEspecialidad((i - 1) % 5 + 1);
        int dia = (i % 28) + 1;
        int mes = (i <= 10 ? 6 : 7);
        t.setFechaAtencion(Fecha(dia, mes, 2025));
        t.setImporteConsulta(1000.0f + i * 10);
        t.setCancelado(i % 4 == 0);
        t.setAsistio(i % 4 != 0);
        archivoTurno.Guardar(t);
    }

    cout << "20 turnos cargados." << endl << endl;
}


void ejecutarCargaDatosPrueba() {
    cout << "=== INICIO DE CARGA DE DATOS DE PRUEBA ===" << endl << endl;

    limpiarArchivos();
    cargarEspecialidades();
    cargarMedicos();
    cargarPacientes();
    cargarMedicoEspecialidad();
    cargarTurnos();

    cout << "=== CARGA COMPLETA ===" << endl;
}

