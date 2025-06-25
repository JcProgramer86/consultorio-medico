#include "ArchivoTurno.h"
#include <cstdio>
#include <iostream>

// Constructor
ArchivoTurno::ArchivoTurno(std::string nombreArchivoTurno) {
    _nombreArchivoTurno = nombreArchivoTurno;
}

// Guardar al final
bool ArchivoTurno::Guardar(Turno turno) {
    FILE* pArchivo = fopen(_nombreArchivoTurno.c_str(), "ab");
    if (pArchivo == NULL) return false;
    bool ok = fwrite(&turno, sizeof(Turno), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

// Guardar en posición específica
bool ArchivoTurno::Guardar(Turno turno, int posicion) {
    FILE* pArchivo = fopen(_nombreArchivoTurno.c_str(), "rb+");
    if (pArchivo == NULL) return false;
    fseek(pArchivo, sizeof(Turno) * posicion, SEEK_SET);
    bool ok = fwrite(&turno, sizeof(Turno), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

// Buscar por ID
int ArchivoTurno::Buscar(int IDTurno) {
    FILE* pArchivo = fopen(_nombreArchivoTurno.c_str(), "rb");
    if (pArchivo == NULL) return -1;
    Turno turno;
    int i = 0;
    while (fread(&turno, sizeof(Turno), 1, pArchivo)) {
        if (turno.getId() == IDTurno) {
            fclose(pArchivo);
            return i;
        }
        i++;
    }
    fclose(pArchivo);
    return -1;
}

// Leer turno por posición
Turno ArchivoTurno::Leer(int posicion) {
    FILE* pArchivo = fopen(_nombreArchivoTurno.c_str(), "rb");
    if (pArchivo == NULL) return Turno();
    Turno turno;
    fseek(pArchivo, sizeof(Turno) * posicion, SEEK_SET);
    fread(&turno, sizeof(Turno), 1, pArchivo);
    fclose(pArchivo);
    return turno;
}

// Contar cantidad de registros
int ArchivoTurno::CantidadRegistros() {
    FILE* pArchivo = fopen(_nombreArchivoTurno.c_str(), "rb");
    if (pArchivo == NULL) return 0;
    fseek(pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(pArchivo) / sizeof(Turno);
    fclose(pArchivo);
    return cantidadRegistros;
}

// Generar nuevo ID (auto-incremental)
int ArchivoTurno::generarNuevoId() {
    int cantidad = CantidadRegistros();
    if (cantidad == 0) return 1;
    Turno ultimo = Leer(cantidad - 1);
    return ultimo.getId() + 1;
}

// Leer un vector de turnos
void ArchivoTurno::Leer(int cantidadRegistros, Turno* vector) {
    FILE* pArchivo = fopen(_nombreArchivoTurno.c_str(), "rb");
    if (pArchivo == NULL) return;
    for (int i = 0; i < cantidadRegistros; i++) {
        fread(&vector[i], sizeof(Turno), 1, pArchivo);
    }
    fclose(pArchivo);
}

