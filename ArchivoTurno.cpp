#include <cstdio>
#include <iostream>
#include <cstring>
#include "ArchivoTurno.h"

using namespace std;

ArchivoTurno::ArchivoTurno(const char* nombreArchivoTurno) {
    strcpy(_nombreArchivoTurno, nombreArchivoTurno);
}

bool ArchivoTurno::GuardarTurno(Turno turno) {
    FILE* pArchivo = fopen(_nombreArchivoTurno, "ab");
    if (pArchivo == nullptr) return false;

    bool ok = fwrite(&turno, sizeof(Turno), 1, pArchivo) == 1;
    fclose(pArchivo);
    return ok;
}

bool ArchivoTurno::ModificarTurno(Turno turno, int posicion) {
    FILE* pArchivo = fopen(_nombreArchivoTurno, "rb+");
    if (pArchivo == nullptr) return false;

    fseek(pArchivo, sizeof(Turno) * posicion, SEEK_SET);
    bool ok = fwrite(&turno, sizeof(Turno), 1, pArchivo) == 1;
    fclose(pArchivo);
    return ok;
}

int ArchivoTurno::BuscarTurnoPorId(int idTurno) {
    FILE* pArchivo = fopen(_nombreArchivoTurno, "rb");
    if (pArchivo == nullptr) return -1;

    Turno turno;
    int i = 0;
    while (fread(&turno, sizeof(Turno), 1, pArchivo) == 1) {
        if (turno.getIdTurno() == idTurno) {
            fclose(pArchivo);
            return i;
        }
        i++;
    }
    fclose(pArchivo);
    return -1;
}

// Implementación de LeerTurno que retorna el objeto Turno
Turno ArchivoTurno::LeerTurno(int posicion) {
    FILE* pArchivo = fopen(_nombreArchivoTurno, "rb");
    if (pArchivo == nullptr) return Turno(); // Retorna un turno por defecto si falla la apertura

    Turno turno;
    fseek(pArchivo, sizeof(Turno) * posicion, SEEK_SET);
    fread(&turno, sizeof(Turno), 1, pArchivo);
    fclose(pArchivo);
    return turno;
}

// Implementación de CantidadRegistros
int ArchivoTurno::CantidadRegistros() {
    FILE* pArchivo = fopen(_nombreArchivoTurno, "rb");
    if (pArchivo == nullptr) return 0;

    fseek(pArchivo, 0, SEEK_END);
    int cantidad = ftell(pArchivo) / sizeof(Turno);
    fclose(pArchivo);
    return cantidad;
}

// Implementación de ListarTurnos
void ArchivoTurno::ListarTurnos() {
    int cantidad = CantidadRegistros();

    if (cantidad == 0) {
        cout << "No hay turnos registrados." << endl;
        return;
    }

    cout << "--- Listado de Turnos ---" << endl;
    for (int i = 0; i < cantidad; i++) {
        Turno turno = LeerTurno(i);
        cout << "-------------------------" << endl;
        cout << "ID Turno: " << turno.getIdTurno() << endl;
        cout << "Fecha: " << turno.getFechaAtencion().toString() << endl;
        cout << "Hora: " << turno.getHoraAtencion().getHoraAtencion() << ":" << turno.getHoraAtencion().getMinutoAtencion() << endl;
        cout << "Importe: $" << turno.getImporteConsulta() << endl;
        cout << "Cancelado: " << (turno.getCancelado() ? "Sí" : "No") << endl;
        cout << "Sobreturno: " << (turno.getSobreturno() ? "Sí" : "No") << endl;
        cout << "Duración: " << turno.getDuracionTurno().getHoraAtencion() << "h " << turno.getDuracionTurno().getMinutoAtencion() << "min" << endl;
        cout << "Observaciones: " << turno.getObservaciones() << endl;

        cout << "ID(s) Paciente(s): ";
        const int* pacientes = turno.getIdPaciente();
        for (int j = 0; j < 10; ++j) {
            if (pacientes[j] != -1) { // Asumiendo -1 como valor nulo
                cout << pacientes[j] << " ";
            }
        }
        cout << endl;

        cout << "ID(s) Medico(s) Especialidad: ";
        const int* medicosEspecialidad = turno.getIdMedicoEspecialidad();
        for (int j = 0; j < 10; ++j) {
            if (medicosEspecialidad[j] != -1) { // Asumiendo -1 como valor nulo
                cout << medicosEspecialidad[j] << " ";
            }
        }
        cout << endl;
    }
    cout << "-------------------------" << endl;
}
