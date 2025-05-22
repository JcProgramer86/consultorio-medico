#include <cstdio>        // fopen, fread, fwrite, fclose, fseek
#include <iostream>      // cout, endl
#include <cstring>       // strcpy
#include "ArchivoTurno.h"

using namespace std;

// Constructor: guarda el nombre del archivo en el atributo privado
ArchivoTurno::ArchivoTurno(const char* nombreArchivoTurno) {
    strcpy(_nombreArchivoTurno, nombreArchivoTurno);  // Copia segura de cadena de C
}

// Guarda un turno al final del archivo (modo "append binary")
bool ArchivoTurno::GuardarTurno(Turno turno) {
    FILE* pArchivo = fopen(_nombreArchivoTurno, "ab");  // Abrir archivo en modo "agregar binario"
    if (pArchivo == nullptr) return false;              // Si no se pudo abrir, error

    bool ok = fwrite(&turno, sizeof(turno), 1, pArchivo) == 1;  // Escribir el turno
    fclose(pArchivo);                                     // Cerrar archivo
    return ok;                                            // Retornar si se escribió bien
}

// Modifica un turno existente en una posición específica
bool ArchivoTurno::ModificarTurno(Turno turno, int posicion) {
    FILE* pArchivo = fopen(_nombreArchivoTurno, "rb+");  // Abrir en modo lectura/escritura binaria
    if (pArchivo == nullptr) return false;               // Error si no se abre

    fseek(pArchivo, sizeof(turno) * posicion, SEEK_SET); // Mover el puntero al turno deseado
    bool ok = fwrite(&turno, sizeof(turno), 1, pArchivo) == 1; // Sobrescribir los datos
    fclose(pArchivo);                                     // Cerrar archivo
    return ok;                                            // Retornar si fue correcto
}

// Lee un turno desde el archivo en una posición dada
bool ArchivoTurno::LeerTurno(Turno& turno, int posicion) {
    FILE* pArchivo = fopen(_nombreArchivoTurno, "rb");
    if (pArchivo == nullptr) return false;

    fseek(pArchivo, sizeof(Turno) * posicion, SEEK_SET);
    bool leyo = fread(&turno, sizeof(Turno), 1, pArchivo) == 1;
    fclose(pArchivo);
    return leyo;
}

// Lista todos los turnos en el archivo imprimiendo sus datos
void ArchivoTurno::ListarTurnos() {
    FILE* pArchivo = fopen(_nombreArchivoTurno, "rb");
    if (pArchivo == nullptr) {
        cout << "No se pudo abrir el archivo de turnos." << endl;
        return;
    }

    Turno turno;
    int contador = 0;
    while (fread(&turno, sizeof(Turno), 1, pArchivo) == 1) {
        cout << "Turno #" << contador << ":" << endl;
        cout << "  ID Turno: " << turno.getIdTurno() << endl;

        cout << "  IDs Pacientes: ";
        const int* pacientes = turno.getIdPaciente();
        for (int i = 0; i < 10; i++) cout << pacientes[i] << " ";
        cout << endl;

        cout << "  IDs Médicos: ";
        const int* medicos = turno.getIdMedico();
        for (int i = 0; i < 10; i++) cout << medicos[i] << " ";
        cout << endl;

        Fecha fecha = turno.getFechaTurno();
        cout << "  Fecha: " << fecha.getDia() << "/" << fecha.getMes() << "/" << fecha.getAnio() << endl;

        Hora hora = turno.getHoraTurno();
        cout << "  Hora: " << hora.getHora() << ":" << hora.getMinuto() << endl;

        cout << "  Importe Consulta: $" << turno.getImporteConsulta() << endl;
        cout << "-----------------------" << endl;
        contador++;
    }

    fclose(pArchivo);
}

// Busca la posición de un turno por su ID, devuelve -1 si no encuentra
int ArchivoTurno::BuscarTurnoPorId(int idTurnoBuscado) {
    FILE* pArchivo = fopen(_nombreArchivoTurno, "rb");
    if (pArchivo == nullptr) return -1;

    Turno turno;
    int posicion = 0;
    while (fread(&turno, sizeof(Turno), 1, pArchivo) == 1) {
        if (turno.getIdTurno() == idTurnoBuscado) {
            fclose(pArchivo);
            return posicion;
        }
        posicion++;
    }
    fclose(pArchivo);
    return -1;
}
