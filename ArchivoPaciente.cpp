#include "Fecha.h"
#include "ArchivoPaciente.h"

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
        if(paciente.get_id() == IDPaciente){ // get_id() is now const
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
        if (paciente.get_nombre() == pacienteNombre) { // get_nombre() is now const
            fclose(pArchivo);
            return i;
        }
        i++;
    }

    fclose(pArchivo);
    return -1;
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

