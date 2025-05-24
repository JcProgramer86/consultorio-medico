#include "ArchivoMedicoEspecialidad.h"
#include <cstdio> // Para fopen, fread, fwrite, fclose, fseek

// Constructor con el nombre del archivo
ArchivoMedicoEspecialidad::ArchivoMedicoEspecialidad(std::string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

// Guardar un registro de MedicoEspecialidad al final del archivo
bool ArchivoMedicoEspecialidad::Guardar(MedicoEspecialidad link) {
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "ab");
    if (pArchivo == NULL) {
        return false;
    }
    bool ok = fwrite(&link, sizeof(MedicoEspecialidad), 1, pArchivo) == 1;
    fclose(pArchivo);
    return ok;
}

// Guardar un registro de MedicoEspecialidad en una posición específica del archivo
bool ArchivoMedicoEspecialidad::Guardar(MedicoEspecialidad link, int posicion) {
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb+");
    if (pArchivo == NULL) {
        return false;
    }
    fseek(pArchivo, sizeof(MedicoEspecialidad) * posicion, SEEK_SET);
    bool ok = fwrite(&link, sizeof(MedicoEspecialidad), 1, pArchivo) == 1;
    fclose(pArchivo);
    return ok;
}

// Leer un registro de MedicoEspecialidad de una posición específica
MedicoEspecialidad ArchivoMedicoEspecialidad::Leer(int posicion) {
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == NULL) {
        return MedicoEspecialidad(); // Retorna un objeto vacío si no se puede abrir el archivo
    }
    MedicoEspecialidad link;
    fseek(pArchivo, sizeof(MedicoEspecialidad) * posicion, SEEK_SET);
    fread(&link, sizeof(MedicoEspecialidad), 1, pArchivo);
    fclose(pArchivo);
    return link;
}

// Buscar un enlace específico (médico-especialidad) y devuelve su posición
int ArchivoMedicoEspecialidad::Buscar(int idMedico, int idEspecialidad) {
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == NULL) {
        return -1; // No se puede abrir el archivo
    }
    MedicoEspecialidad link;
    int i = 0;
    while (fread(&link, sizeof(MedicoEspecialidad), 1, pArchivo) == 1) {
        if (link.getIdMedico() == idMedico && link.getIdEspecialidad() == idEspecialidad) {
            fclose(pArchivo);
            return i; // Se encontró el enlace en la posición i
        }
        i++;
    }
    fclose(pArchivo);
    return -1; // No se encontró el enlace
}

// Obtener el total de registros en el archivo
int ArchivoMedicoEspecialidad::CantidadRegistros() {
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == NULL) {
        return 0; // No hay registros si no se puede abrir el archivo
    }
    fseek(pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(pArchivo) / sizeof(MedicoEspecialidad);
    fclose(pArchivo);
    return cantidadRegistros;
}
