#include "ArchivoEspecialidad.h"
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

ArchivoEspecialidad::ArchivoEspecialidad(std::string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}


bool ArchivoEspecialidad::guardar(Especialidad especialidad) {
    // Abro el archivo en modo "append binary" para agregar al final
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "ab");
    if (pArchivo == nullptr) {
        cout << "No se pudo abrir el archivo para guardar." << endl;
        return false; // Si no se pudo abrir el archivo, retorno false
    }
    // Escribo el registro en el archivo
    bool ok = fwrite(&especialidad, sizeof(Especialidad), 1, pArchivo);
    fclose(pArchivo); // Siempre cerrar el archivo
    return ok; // Devuelvo true si se pudo escribir, false si no
}

bool ArchivoEspecialidad::guardar(Especialidad especialidad, int posicion) {
    // Abro el archivo en modo lectura/escritura para modificar un registro existente
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb+");
    if (pArchivo == nullptr) {
        cout << "No se pudo abrir el archivo para modificar." << endl;
        return false;
    }
    // Me posiciono en el registro indicado (posicion * tamaño de registro)
    fseek(pArchivo, sizeof(Especialidad) * posicion, SEEK_SET);
    // Sobrescribo el registro con la especialidad nueva
    bool ok = fwrite(&especialidad, sizeof(Especialidad), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

int ArchivoEspecialidad::buscarPorCodigo(const char* codigo) {
    // Abro el archivo en modo lectura binaria
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == nullptr) {
        return -1; // Si no se pudo abrir el archivo retorno -1
    }

    Especialidad especialidad;
    int i = 0;

    // Leo registro por registro hasta encontrar el código o llegar al final
    while (fread(&especialidad, sizeof(Especialidad), 1, pArchivo)) {
        // Comparo el código buscado con el código del registro actual
        if (strcmp(especialidad.get_codEspecialidad(), codigo) == 0) {
            fclose(pArchivo);
            return i; // Devuelvo la posición donde encontré el código
        }
        i++;
    }

    fclose(pArchivo);
    return -1; // No encontré el código
}

int ArchivoEspecialidad::buscarPorId(int id) {
    // Abro el archivo en modo lectura binaria
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == nullptr) {
        return -1; // Retorno -1 si no se puede abrir
    }

    Especialidad especialidad;
    int i = 0;

    // Recorro el archivo buscando el id igual al solicitado
    while (fread(&especialidad, sizeof(Especialidad), 1, pArchivo)) {
        if (especialidad.get_id() == id) {
            fclose(pArchivo);
            return i; // Devuelvo la posición
        }
        i++;
    }

    fclose(pArchivo);
    return -1; // No encontrado
}

Especialidad ArchivoEspecialidad::leer(int posicion) {
    // Abro el archivo para lectura binaria
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    Especialidad especialidad;

    if (pArchivo == nullptr) {
        cout << "No se pudo abrir el archivo para leer." << endl;
        return especialidad; // Retorno objeto vacío
    }

    // Me posiciono en el registro deseado
    fseek(pArchivo, sizeof(Especialidad) * posicion, SEEK_SET);
    // Leo el registro completo
    fread(&especialidad, sizeof(Especialidad), 1, pArchivo);
    fclose(pArchivo);

    return especialidad; // Devuelvo el registro leído
}

Especialidad ArchivoEspecialidad::leerPorId(int id) {
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == NULL) {
        return Especialidad(); // objeto vacío
    }

    Especialidad esp;
    while (fread(&esp, sizeof(Especialidad), 1, pArchivo)) {
        if (esp.get_id() == id) {
            fclose(pArchivo);
            return esp;
        }
    }

    fclose(pArchivo);
    return Especialidad(); // si no lo encuentra
}


int ArchivoEspecialidad::cantidadRegistros() {
    // Abro el archivo para lectura binaria
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == nullptr) {
        return 0; // Si no se pudo abrir el archivo, digo que no hay registros
    }

    // Voy al final del archivo
    fseek(pArchivo, 0, SEEK_END);
    // Calculo la cantidad de registros dividiendo el tamaño total por tamaño de un registro
    int cantidad = ftell(pArchivo) / sizeof(Especialidad);
    fclose(pArchivo);

    return cantidad;
}

void ArchivoEspecialidad::leer(int cantidadRegistros, Especialidad* vector) {
    // Abro el archivo para lectura binaria
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == nullptr) {
        return; // No hago nada si no se pudo abrir
    }

    // Leo registros en bloque y los guardo en el vector recibido
    for (int i = 0; i < cantidadRegistros; i++) {
        fread(&vector[i], sizeof(Especialidad), 1, pArchivo);
    }

    fclose(pArchivo);
}
