#include "Fecha.h"
#include "ArchivoPaciente.h"
#include <iostream>

ArchivoPaciente::ArchivoPaciente(std::string nombreArchivo){
    _nombreArchivo = nombreArchivo;
}

bool ArchivoPaciente::Guardar(Paciente paciente){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "ab");
    if(pArchivo == NULL){
        return false;
    }
    bool ok = fwrite(&paciente, sizeof(Paciente), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

int ArchivoPaciente::generarNuevoId() {
    int cantidad = CantidadRegistros();
    if (cantidad == 0) return 1;

    Paciente ultimo = Leer(cantidad - 1);
    return ultimo.get_id() + 1;
}

bool ArchivoPaciente::Guardar(Paciente paciente, int posicion){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb+");
    if(pArchivo == NULL){
        return false;
    }
    fseek(pArchivo, sizeof(Paciente) * posicion, SEEK_SET);
    bool ok = fwrite(&paciente, sizeof(Paciente), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

int ArchivoPaciente::Buscar(int IDPaciente){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return -1;
    }

    Paciente paciente;
    int i = 0;

    while(fread(&paciente, sizeof(Paciente), 1, pArchivo)){
        if(paciente.get_id() == IDPaciente){
            fclose(pArchivo);
            return i;
        }
        i++;
    }

    fclose(pArchivo);
    return -1;
}

int ArchivoPaciente::BuscarPorNombre(std::string& pacienteNombre) {
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == NULL) {
        return -1;
    }
    Paciente paciente;
    int i = 0;

    while (fread(&paciente, sizeof(Paciente), 1, pArchivo)) {
        if (paciente.get_nombre() == pacienteNombre) {
            fclose(pArchivo);
            return i;
        }
        i++;
    }

    fclose(pArchivo);
    return -1;
}

int ArchivoPaciente::BuscarPorDni(std::string& dniPaciente) {
    FILE* pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if (pArchivo == NULL) {
        return -1;
    }
    Paciente paciente;
    int i = 0;

    while (fread(&paciente, sizeof(Paciente), 1, pArchivo)) {
        if (paciente.get_dni() == dniPaciente) {
            fclose(pArchivo);
            return i;
        }
        i++;
    }

    fclose(pArchivo);
    return -1;
}

bool ArchivoPaciente::checkDni(std::string& dni){
    int pos = BuscarPorDni(dni);
    if (pos != -1) {
        std::cout << "El DNI ya está registrado para otro paciente." << std::endl;
        return false;
    }
    return true;
}

Paciente ArchivoPaciente::Leer(int posicion){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return Paciente();
    }

    Paciente paciente;

    fseek(pArchivo, sizeof(Paciente) * posicion, SEEK_SET);
    fread(&paciente, sizeof(Paciente), 1, pArchivo);
    fclose(pArchivo);

    return paciente;
}

int ArchivoPaciente::CantidadRegistros(){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return 0;
    }

    fseek(pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(pArchivo) / sizeof(Paciente);
    fclose(pArchivo);

    return cantidadRegistros;
}

void ArchivoPaciente::Leer(int cantidadRegistros, Paciente *vector){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return;
    }

    for(int i = 0; i < cantidadRegistros; i++){
        fread(&vector[i], sizeof(Paciente), 1, pArchivo);
    }

    fclose(pArchivo);
}

